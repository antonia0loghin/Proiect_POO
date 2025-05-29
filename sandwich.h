#ifndef SANDWICH_H
#define SANDWICH_H

#include "product.h"

class Sandwich : public Product {
public:
    Sandwich();
    Sandwich(const std::string& name, double price, int cook_time);
    std::string GetCategory() const override;
    std::string GetPreferredDeviceType() const override;

};

#endif
