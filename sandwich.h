#ifndef SANDWICH_H
#define SANDWICH_H

#include "product.h"

class Sandwich : public Product {
public:
    Sandwich();
    std::string GetCategory() const override;
};

#endif
