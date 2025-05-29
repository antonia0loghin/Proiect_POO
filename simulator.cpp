#include "simulator.h"
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <thread>
#include <chrono>
#include "simulator.h"
#include "cafe.h"
void Simulator::Run() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // pentru randomness
    std::cout << " Welcome to the Barista Simulator!\n";

    // Nume posibile pentru clienți
    std::vector<std::string> namePool = {"Ana", "Luca", "Zoe", "Denis", "Mara", "Radu"};
    int numClients = 1 + rand() % 5;

    std::cout << "Today's clients:\n";
    for (int i = 0; i < numClients; ++i) {
        std::string name = namePool[rand() % namePool.size()];
        std::cout << "- " << name << "\n";
        m_cafe.AddClient(name);
    }

    std::cout << "\n Generating random orders...\n";
    m_cafe.GenerateRandomOrders();

    bool running = true;
    while (running) {
        std::cout << "\n What would you like to do?\n";
        std::cout << "1. Serve clients\n";
        std::cout << "2. Show stats\n";
        std::cout << "3. Exit\n";
        std::cout << " Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                m_cafe.ServeClients(this); //  pass pointer la self
                break;
            }

            case 2:
                Stats::PrintStats();
                break;

            case 3:
                running = false;
                std::cout << " Closing up the café. See you next shift!\n";
                m_cafe.ClearClients();
                break;

            default:
                std::cout << " Invalid option. Try again!\n";
                break;
        }
    }
}

Cafe& Simulator::GetCafe() { return m_cafe; }
TimeManager& Simulator::GetTime() { return m_time; }

void Simulator::TickTime(int seconds) {
    for (int t = 0; t < seconds; ++t) {
        m_time.AdvanceTime(1);
        m_cafe.AdvanceDevicesCooldown();
        m_cafe.AdvanceClientTimers();

        std::cout << "[Tick " << t + 1 << "] Time passed...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // timp real
    }
}



