#include "order.h"
#include <iostream>

Order::Order(int id) : m_order_id(id) {}

void Order::AddProduct(std::shared_ptr<Product> product) {
    m_products.push_back(product);
}

void Order::PrintOrder() const {
    std::cout << "Order #" << m_order_id << " contains:" << std::endl;
    for (const auto& product : m_products) {
        product->Print();  // sau std::cout << product << std::endl;
    }
}

int Order::GetTotalTime() const {
    int total = 0;
    for (const auto& product : m_products) {
        total += product->GetCookTime();
    }
    return total;
}
