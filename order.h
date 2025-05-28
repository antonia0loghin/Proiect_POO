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
    Order(int id);
    void AddProduct(std::shared_ptr<Product> product);
    void PrintOrder() const;
    int GetTotalTime() const;
    const std::vector<std::shared_ptr<Product>>& GetProducts() const;

};

#endif
