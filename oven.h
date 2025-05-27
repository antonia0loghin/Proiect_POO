#ifndef OVEN_H
#define OVEN_H

#include "device.h"

class Oven : public Device {
public:
    Oven();
    void Use() override;
    std::string GetType() const override;
};

#endif
