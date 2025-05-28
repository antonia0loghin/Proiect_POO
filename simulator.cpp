#include "simulator.h"
#include <iostream>

#include <cstdlib>
#include <ctime>

void Simulator::Run() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // pentru randomness

    std::cout << "Welcome to the Barista Simulator!\n";

    std::vector<std::string> namePool = { "Ana", "Denis", "Zoe", "Luca", "Radu", "Mara" };
    int numClients = 1 + rand() % 5;

    std::cout << "Today we'll have " << numClients << " clients:\n";

    for (int i = 0; i < numClients; ++i) {
        std::string name = namePool[rand() % namePool.size()];
        std::cout << "- " << name << "\n";
        m_cafe.AddClient(name);
    }

    
    m_cafe.GenerateRandomOrders();

    // Meniu principal
    bool running = true;
    while (running) {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Serve clients\n";
        std::cout << "2. Show stats\n";
        std::cout << "3. Exit simulator\n";
        std::cout << " Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            m_cafe.ServeClients(); // timpul e gestionat automat aici
            break;

        case 2:
            Stats::PrintStats();
            break;

        case 3:
            running = false;
            std::cout << "Exiting simulator. Have a great day!\n";
            break;

        default:
            std::cout << "Invalid choice, try again.\n";
            break;
        }
    }
}


void Simulator::AdvanceTime(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        m_time.AdvanceTime(1);
        m_cafe.AdvanceDevicesCooldown();
        m_cafe.AdvanceClientTimers();
        std::cout << "[Time Tick] Devices updated. Clients getting impatient...\n";
    }
}

