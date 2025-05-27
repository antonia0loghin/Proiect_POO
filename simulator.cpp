#include "simulator.h"
#include <iostream>

void Simulator::Run() {
    std::cout << " Welcome to the Barista Simulator!\n";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<std::string> namePool = { "Ana", "Denis", "Zoe", "Luca", "Radu", "Mara" };
    int numClients = 1 + rand() % 5;

    std::cout << "Today we'll have " << numClients << " clients:\n";

    for (int i = 0; i < numClients; ++i) {
        std::string name = namePool[rand() % namePool.size()];
        std::cout << "- " << name << "\n";
        m_cafe.AddClient(name);
    }

    std::cout << "\nGenerating random orders...\n";
    m_cafe.GenerateRandomOrders();

    // User options
    bool running = true;
    while (running) {
        std::cout << "\n What would you like to do?\n";
        std::cout << "1. Serve clients\n";
        std::cout << "2. Advance time\n";
        std::cout << "3. Show stats\n";
        std::cout << "4. Exit simulator\n";
        std::cout << " Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            m_cafe.ServeClients();
            break;
        case 2:
            m_time.AdvanceTime(5);
            break;
        case 3:
            Stats::PrintStats();
            break;
        case 4:
            running = false;
            std::cout << " Exiting simulator. Have a great day!\n";
            break;
        default:
            std::cout << " Invalid choice, try again.\n";
            break;
        }
    }
}
