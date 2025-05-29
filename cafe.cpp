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

#include "coffee_pot.h"
#include "sandwich_maker.h"
#include "oven.h"
#include "simulator.h"

Cafe::Cafe() : m_next_order_id(1) {
    m_devices.emplace_back(new CoffeePot());
    m_devices.emplace_back(new SandwichMaker());
    m_devices.emplace_back(new Oven());
}

void Cafe::AddClient(const std::string& name) {
    Client newClient(name, m_next_order_id++);

    //  creează o comandă
    Order& order = newClient.GetOrder();

    //  randomizare număr produse (1-3)
    int productCount = 1 + rand() % 3;

    for (int i = 0; i < productCount; ++i) {
        int pick = rand() % 3;

        switch (pick) {
            case 0:
                order.AddProduct(std::make_shared<Coffee>());
                break;
            case 1:
                order.AddProduct(std::make_shared<Sandwich>());
                break;
            case 2:
                order.AddProduct(std::make_shared<Cookie>());
                break;
        }
    }

    m_clients.emplace_back(std::move(newClient));
}


void Cafe::ServeClients(Simulator* sim) {
    if (m_clients.empty()) {
        std::cout << "\n☕ No more clients waiting in the café!\n";
        return;
    }

    //  Copie de backup ca să nu iterăm pe vector modificat
    std::vector<std::string> clientNames;
    for (const auto& client : m_clients) {
        clientNames.push_back(client.GetName());
    }

    for (const auto& name : clientNames) {
        //  Căutăm clientul real (doar dacă mai e acolo)
        auto it = std::find_if(m_clients.begin(), m_clients.end(),
            [&](const Client& c) { return c.GetName() == name; });

        if (it == m_clients.end()) {
            std::cout << " Client " << name << " already left. Skipping.\n";
            continue;
        }

        Client& client = *it;
        std::cout << "\n--- Now serving: " << client.GetName() << " ---\n";
        const Order& order = client.GetOrder();
        const auto& products = order.GetProducts();

        for (size_t i = 0; i < products.size(); ++i) {
            if (!products[i]) {
                std::cout << "[ERROR] Product #" << i + 1 << " is null. Skipping...\n";
                continue;
            }

            std::cout << "\nProduct #" << (i + 1) << ": ";
            products[i]->Print();

            std::cout << "Choose a device to use:\n";
            for (size_t j = 0; j < m_devices.size(); ++j) {
                std::cout << j + 1 << ". " << m_devices[j]->GetName()
                          << " (Category: " << m_devices[j]->GetCompatibleCategory() << ")\n";
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
            sim->TickTime(1); // ⏱️ timp trece pentru alegere

            if (chosenDevice->GetCompatibleCategory() != products[i]->GetCategory()) {
                std::cout << "\n[ERROR] Wrong device!\n";
                std::cout << "Client " << client.GetName() << " stormed out!\n";
                sim->TickTime(3); // penalizare
                return;
            }

            if (chosenDevice->IsReady()) {
                std::cout << "Using " << chosenDevice->GetName() << "...\n";
                chosenDevice->Use();
                Stats::AddRevenue(products[i]->GetPrice());

                int cookTime = products[i]->GetCookTime();
                std::cout << "⏳ Preparing for " << cookTime << " seconds...\n";
                sim->TickTime(cookTime); // timp real
            } else {
                std::cout << "Device cooling down. Skipping product.\n";
                sim->TickTime(1); // mic delay
            }

            // Verificăm dacă clientul a plecat în timpul tick-urilor
            auto check = std::find_if(m_clients.begin(), m_clients.end(),
                [&](const Client& c) { return c.GetName() == name; });

            if (check == m_clients.end()) {
                std::cout << "⚠ Client " << name << " has left mid-order!\n";
                break;
            }
        }

        // Dacă clientul nu a plecat, îl marcăm ca servit
        auto confirm = std::find_if(m_clients.begin(), m_clients.end(),
            [&](const Client& c) { return c.GetName() == name; });

        if (confirm != m_clients.end()) {
            Stats::AddClientServed();
            std::cout << " Client " << name << " has been served!\n";
        }
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
        std::cout << "Client " << name << " has left the cafe! " << quote << "\n";
    }
}
std::vector<std::unique_ptr<Device>>& Cafe::GetDevices() {
    return m_devices;
}

void Cafe::ClearClients() {
    m_clients.clear();
}
