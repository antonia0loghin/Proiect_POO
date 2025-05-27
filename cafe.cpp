#include "cafe.h"
#include "coffee.h"
#include "sandwich.h"
#include "cookie.h"
#include <cstdlib> // rand
#include <ctime>   // time (optional, poate deja ai dat srand() in simulator)
#include <memory>  // shared_ptr
#include <limits>

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
            std::cout << "\nProduct #" << (i + 1) << ": " << *products[i] << "\n";
            std::cout << "Choose a device to use:\n";

            for (size_t j = 0; j < m_devices.size(); ++j) {
                std::cout << j + 1 << ". " << m_devices[j]->GetName() << "\n";
            }

            int deviceChoice = 0;
            while (deviceChoice < 1 || deviceChoice > m_devices.size()) {
                std::cout << "Enter choice: ";
                std::cin >> deviceChoice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    deviceChoice = 0;
                }
            }

            Device* chosenDevice = m_devices[deviceChoice - 1].get();
            if (chosenDevice->IsReady()) {
                std::cout << "Using " << chosenDevice->GetName() << "...\n";
                chosenDevice->Use();
                Stats::AddRevenue(products[i]->GetPrice());
            }
            else {
                std::cout << "Device not ready. Skipping this product.\n";
            }
        }

        Stats::AddClientServed();
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
