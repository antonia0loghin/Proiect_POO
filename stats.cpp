#include "stats.h"
#include <iostream>

int Stats::s_clients_served = 0;
double Stats::s_total_revenue = 0.0;

void Stats::AddClientServed() {
    ++s_clients_served;
}

void Stats::AddRevenue(double amount) {
    s_total_revenue += amount;
}

void Stats::PrintStats() {
    std::cout << "Clients served: " << s_clients_served
        << " | Total revenue: $" << s_total_revenue << "\n";
}
