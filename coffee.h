#ifndef COFFEE_H
#define COFFEE_H

#include "product.h"

class Coffee : public Product {
public:
    Coffee();
    Coffee(const std::string& name, double price, int cook_time);
    std::string GetCategory() const override;
    std::string GetPreferredDeviceType() const override;

};

#endif
