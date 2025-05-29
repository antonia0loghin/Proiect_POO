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


void Client::DecreasePatience() {
    if (m_patience_seconds > 0)
        --m_patience_seconds;
}

bool Client::IsStillWaiting() const {
    return m_patience_seconds > 0;
}

Client::Client(std::string name)
    : m_name(std::move(name)), m_order() // foloseste Order() default
{
    std::cout << "[Client] Created with empty order\n";
}

Client::Client(std::string name, Order order)
    : m_name(std::move(name)), m_order(std::move(order)) // foloseste Order(id) sau Order(id, produse)
{
    std::cout << "[Client] Created with custom order\n";
}


void Client::PrintOrder() const {
    const auto& products = m_order.GetProducts();
    std::cout << "Client " << m_name << "'s order:\n";
    for (const auto& p : products) {
        p->Print();
    }
}