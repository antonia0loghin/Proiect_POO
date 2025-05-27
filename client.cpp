#include "client.h"
#include <iostream>

Client::Client(std::string name, int order_id)
    : m_name(name), m_order(order_id) {
}

void Client::PrintClientInfo() const {
    std::cout << "Client: " << m_name << std::endl;
    m_order.PrintOrder();
}

Order& Client::GetOrder(){
    return m_order;
}

std::string Client::GetName() const {
    return m_name;
}
