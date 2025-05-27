#ifndef STATS_H
#define STATS_H

class Stats {
private:
    static int s_clients_served;
    static double s_total_revenue;

public:
    static void AddClientServed();
    static void AddRevenue(double amount);
    static void PrintStats();
};

#endif
