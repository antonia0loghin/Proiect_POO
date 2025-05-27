#include "product.h"
#include <iostream>

Product::Product(std::string name, int cookTime, double price)
    : m_name(name), m_cook_time(cookTime), m_price(price) {
}

Product::~Product() {
    // Destructor simplu
}

void Product::Print() const {
    std::cout << "Product: " << m_name
        << " | Time: " << m_cook_time << "s"
        << " | Price: $" << m_price << std::endl;
}

int Product::GetCookTime() const {
    return m_cook_time;
}

double Product::GetPrice() const {
    return m_price;
}

std::string Product::GetName() const {
    return m_name;
}

std::ostream& operator<<(std::ostream& out, const Product& p) {
    out << p.m_name << " ($" << p.m_price << ", " << p.m_cook_time << "s)";
    return out;
}
