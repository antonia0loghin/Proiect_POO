#ifndef COOKIE_H
#define COOKIE_H

#include "product.h"

class Cookie : public Product {
public:
    Cookie();
    Cookie(const std::string& name, double price, int cook_time);
    std::string GetCategory() const override;
    std::string GetPreferredDeviceType() const override;

};

#endif
