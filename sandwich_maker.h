#ifndef SANDWICH_MAKER_H
#define SANDWICH_MAKER_H

#include "device.h"

class SandwichMaker : public Device {
public:
    SandwichMaker();
    void Use() override;
    
};

#endif
