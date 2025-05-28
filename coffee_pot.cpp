#include "coffee_pot.h"
#include <iostream>

CoffeePot::CoffeePot()
    : Device("Coffee Pot", 2, "Drink") {
}

void CoffeePot::Use() {
    std::cout << "Brewing coffee...\n";
    m_cooldown = 2;
}
