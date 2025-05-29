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
    std::vector<std::shared_ptr<Product>> products;

    int numProducts = 1 + rand() % 3;

    for (int i = 0; i < numProducts; ++i) {
        int pick = rand() % 3;

        switch (pick) {
        case 0:
            products.push_back(std::make_shared<Coffee>("Latte", 6.0, 4));
            break;
        case 1:
            products.push_back(std::make_shared<Sandwich>("Panini", 7.5, 5));
            break;
        case 2:
            products.push_back(std::make_shared<Cookie>("Brownie", 3.5, 2));
            break;
        }
    }

    int id = m_next_order_id++;

    //  folosim overload pentru Order si Client
    Order o(id, products);
    Client c(name, o);

    m_clients.push_back(c); 
}


void Cafe::ServeClients(Simulator* sim) {
    if (m_clients.empty()) {
        std::cout << "\n No more clients waiting in the cafe!\n";
        return;
    }

    //  Copie de backup ca sa nu iteram pe vector modificat
    std::vector<std::string> clientNames;
    for (const auto& client : m_clients) {
        clientNames.push_back(client.GetName());
    }

    for (const auto& name : clientNames) {
        //  Cautam clientul real (doar daca mai e acolo)
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
            sim->TickTime(1); // ⏱ timp trece pentru alegere

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
                std::cout << " Preparing for " << cookTime << " seconds...\n";
                sim->TickTime(cookTime); 
            } else {
                std::cout << "Device cooling down. Skipping product.\n";
                sim->TickTime(1); // mic delay
            }

            // Verificam daca clientul a plecat în timpul tick-urilor
            auto check = std::find_if(m_clients.begin(), m_clients.end(),
                [&](const Client& c) { return c.GetName() == name; });

            if (check == m_clients.end()) {
                std::cout << "⚠ Client " << name << " has left mid-order!\n";
                break;
            }
        }

        // Daca clientul nu a plecat, il marcam ca servit
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
        Order& order = client.GetOrder();

        //  Add 1-2 random products
        int num = 1 + rand() % 2;
        for (int i = 0; i < num; ++i) {
            int p = rand() % 3;
            if (p == 0) order.AddProduct("Coffee");
            else if (p == 1) order.AddProduct("Sandwich");
            else order.AddProduct("Cookie");
        }

        //  Bonus: adauga un produs fix în functie de nume
        if (client.GetName() == "Zoe") {
            order.AddProduct("Cookie"); 
        }
        else if (client.GetName() == "Denis") {
            order.AddProduct("Coffee"); 
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

    // Eliminam clientii nervosi
    m_clients.erase(
        std::remove_if(m_clients.begin(), m_clients.end(),
            [](const Client& c) { return !c.IsStillWaiting(); }),
        m_clients.end()
    );

    // Mesaje
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
