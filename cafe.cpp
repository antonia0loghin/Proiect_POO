#include "cafe.h"
#include "coffee.h"
#include "sandwich.h"
#include "cookie.h"
#include "stats.h"
#include <cstdlib> // rand
#include <ctime>   // time (optional, poate deja ai dat srand() in simulator)
#include <memory>  // shared_ptr
#include <limits>
#include <algorithm>

Cafe::Cafe() : m_next_order_id(1) {
    m_devices.emplace_back(new CoffeePot());
    m_devices.emplace_back(new SandwichMaker());
    m_devices.emplace_back(new Oven());
}

void Cafe::AddClient(const std::string& name) {
    m_clients.emplace_back(name, m_next_order_id++);
}

#include <limits>

void Cafe::ServeClients() {
    for (auto& client : m_clients) {
        std::cout << "\n--- Now serving: " << client.GetName() << " ---\n";
        const Order& order = client.GetOrder();
        const std::vector<std::shared_ptr<Product>>& products = order.GetProducts();

        for (size_t i = 0; i < products.size(); ++i) {
            std::cout << "\nProduct #" << (i + 1) << ": ";
            products[i]->Print();

            std::cout << "Choose a device to use:\n";
            for (size_t j = 0; j < m_devices.size(); ++j) {
                std::cout << j + 1 << ". " << m_devices[j]->GetName()
                    << " (category: " << m_devices[j]->GetCompatibleCategory() << ")\n";
            }

            int deviceChoice = 0;
            while (deviceChoice < 1 || deviceChoice > static_cast<int>(m_devices.size())) {
                std::cout << "Enter device number: ";
                std::cin >> deviceChoice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    deviceChoice = 0;
                }
            }

            Device* chosenDevice = m_devices[deviceChoice - 1].get();

            // ❌ Verificare compatibilitate device - produs
            if (chosenDevice->GetCompatibleCategory() != products[i]->GetCategory()) {
                std::cout << "\n[ERROR] Wrong device!\n";
                std::cout << "You tried to prepare a " << products[i]->GetName()
                    << " (category: " << products[i]->GetCategory() << ") "
                    << "using a " << chosenDevice->GetName()
                    << " (compatible with: " << chosenDevice->GetCompatibleCategory() << ").\n";
                std::cout << "Client stormed out of the café! Serving session failed.\n";
                return; // oprește servirea tuturor clienților
            }

            // Device e bun
            if (chosenDevice->IsReady()) {
                std::cout << "Using " << chosenDevice->GetName() << "...\n";
                chosenDevice->Use();
                Stats::AddRevenue(products[i]->GetPrice());

                int cookTime = products[i]->GetCookTime();
                std::cout << "Preparing for " << cookTime << " seconds...\n";
                for (int t = 0; t < cookTime; ++t) {
                    
                    AdvanceDevicesCooldown();
                    AdvanceClientTimers();
                    std::cout << ".";
                }
                std::cout << "\nDone!\n";
            }
            else {
                std::cout << "Device is still cooling down. Skipping product.\n";
            }
        }

        Stats::AddClientServed();
        std::cout << "Client " << client.GetName() << " has been served! \n";
    }
}




void Cafe::PrintStatus() const {
    std::cout << "Cafe has " << m_clients.size() << " clients.\n";
    for (const auto& device : m_devices) {
        std::cout << "Device: " << device->GetName() << "\n";
    }
}

void Cafe::GenerateRandomOrders() {
    for (auto& client : m_clients) {
        int numItems = 1 + rand() % 3; // 1 - 3 products per order

        for (int i = 0; i < numItems; ++i) {
            int productType = rand() % 3;

            if (productType == 0) {
                client.GetOrder().AddProduct(std::make_shared<Coffee>());
            }
            else if (productType == 1) {
                client.GetOrder().AddProduct(std::make_shared<Sandwich>());
            }
            else {
                client.GetOrder().AddProduct(std::make_shared<Cookie>());
            }
        }
    }
}

void Cafe::AdvanceDevicesCooldown() {
    for (auto& device : m_devices) {
        device->Tick();
    }
}

void Cafe::AdvanceClientTimers() {
    std::vector<std::string> goneClients;

    for (auto& client : m_clients) {
        client.DecreasePatience();
        if (!client.IsStillWaiting()) {
            goneClients.push_back(client.GetName());
        }
    }

    // Eliminăm clienții nervoși
    m_clients.erase(
        std::remove_if(m_clients.begin(), m_clients.end(),
            [](const Client& c) { return !c.IsStillWaiting(); }),
        m_clients.end()
    );

    // DRAMA MESSAGES 
    std::vector<std::string> rageQuotes = {
        "This place is a disaster!",
        "I'm leaving a 1-star review!",
        "Never coming back here again!",
        "Where is my sandwich?!",
        "This coffee is slower than my grandma!",
        "Worst service ever!",
        "I waited a whole decade!"
    };

    for (const auto& name : goneClients) {
        std::string quote = rageQuotes[rand() % rageQuotes.size()];
        std::cout << "Client " << name << " has left the café! " << quote << "\n";
    }
}