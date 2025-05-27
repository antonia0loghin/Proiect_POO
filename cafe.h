#ifndef CAFE_H
#define CAFE_H

#include <vector>
#include <memory>
#include "device.h"
#include "coffee_pot.h"
#include "sandwich_maker.h"
#include "oven.h"
#include "client.h"

class Cafe {
private:
    std::vector<std::unique_ptr<Device>> m_devices;
    std::vector<Client> m_clients;
    int m_next_order_id;

public:
    Cafe();
    void AddClient(const std::string& name);
    void ServeClients();
    void PrintStatus() const;
	void GenerateRandomOrders();
};

#endif
