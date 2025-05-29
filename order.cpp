#include "order.h"
#include <iostream>
#include "coffee.h"
#include "sandwich.h"
#include "cookie.h"

Order::Order() : m_order_id(0) {
    std::cout << "[Order] Created empty order with ID 0\n";
}

Order::Order(int id) : m_order_id(id) {
    std::cout << "[Order] Created order with ID: " << m_order_id << "\n";
}

Order::Order(int id, const std::vector<std::shared_ptr<Product>>& products)
    : m_order_id(id), m_products(products) {
    std::cout << "[Order] Created order with ID: " << m_order_id << " and "
        << products.size() << " products\n";
}

void Order::AddProduct(std::shared_ptr<Product> p) {
    m_products.push_back(p);
}

void Order::AddProduct(const std::string& name) {
    if (name == "Coffee") {
        m_products.push_back(std::make_shared<Coffee>());
    }
    else if (name == "Sandwich") {
        m_products.push_back(std::make_shared<Sandwich>());
    }
    else if (name == "Cookie") {
        m_products.push_back(std::make_shared<Cookie>());
    }
    else {
        std::cout << "[WARNING] Unknown product name: " << name << "\n";
    }
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

const std::vector<std::shared_ptr<Product>>& Order::GetProducts() const {
    return m_products;
}

Order Order::operator+(const Order& other) const {
    Order result(this->m_order_id);
    for (const auto& product : this->m_products) {
        result.AddProduct(product);
    }
    for (const auto& product : other.m_products) {
        result.AddProduct(product);
    }
    return result;
}