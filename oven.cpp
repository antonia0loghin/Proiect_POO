#include "oven.h"
#include <iostream>

Oven::Oven() : Device("Oven", 4, "Dessert") {}

void Oven::Use() {
    std::cout << "Baking something crispy in the oven..." << std::endl;
    m_cooldown = 4;
}

