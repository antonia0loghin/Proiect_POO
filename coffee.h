#ifndef COFFEE_H
#define COFFEE_H

#include "product.h"

class Coffee : public Product {
public:
    Coffee();
    std::string GetCategory() const override;
    std::string GetPreferredDeviceType() const override;

};

#endif
