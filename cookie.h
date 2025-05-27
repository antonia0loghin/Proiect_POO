#ifndef COOKIE_H
#define COOKIE_H

#include "product.h"

class Cookie : public Product {
public:
    Cookie();
    std::string GetCategory() const override;
};

#endif
