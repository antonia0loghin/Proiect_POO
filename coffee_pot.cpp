#include "coffee_pot.h"
#include <iostream>

CoffeePot::CoffeePot() : Device("Coffee Pot", 2) {}

void CoffeePot::Use() {
    std::cout << "Brewing a hot coffee..." << std::endl;
    m_cooldown = 2;
}

std::string CoffeePot::GetType() const {
    return "CoffeePot";
}
