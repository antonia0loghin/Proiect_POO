#ifndef COFFEE_POT_H
#define COFFEE_POT_H

#include "device.h"

class CoffeePot : public Device {
public:
    CoffeePot();
    void Use() override;
};

#endif
