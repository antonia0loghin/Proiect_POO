#ifndef CAFE_H
#define CAFE_H

#include <vector>
#include <memory>
#include "device.h"

#include "client.h"

class Simulator;

class Cafe {
private:
    std::vector<std::unique_ptr<Device>> m_devices;
    std::vector<Client> m_clients;
    int m_next_order_id;

public:
    Cafe();
    void AddClient(const std::string& name);
    void ServeClients(Simulator *sim);
    void PrintStatus() const;
	void GenerateRandomOrders();
	void AdvanceDevicesCooldown();  
    void AdvanceClientTimers();
    std::vector<std::unique_ptr<Device>>& GetDevices();
    void ClearClients();


};

#endif
