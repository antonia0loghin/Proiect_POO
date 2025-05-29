#pragma once
#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "product.h"
#include <memory>

class Order {
private:
    std::vector<std::shared_ptr<Product>> m_products;
    int m_order_id;

public:
    Order(); // default
    Order(int id); // cu ID
    Order(int id, const std::vector<std::shared_ptr<Product>>& products); // cu produse
    void AddProduct(std::shared_ptr<Product> p);           // original
    void AddProduct(const std::string& name);              // overload 
    void PrintOrder() const;
    int GetTotalTime() const;
    const std::vector<std::shared_ptr<Product>>& GetProducts() const;
	Order operator+(const Order& other) const;
};

#endif
