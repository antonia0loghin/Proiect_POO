#include "oven.h"
#include <iostream>

Oven::Oven() : Device("Oven", 5) {}

void Oven::Use() {
    std::cout << "Baking something crispy in the oven..." << std::endl;
    m_cooldown = 5;
}

std::string Oven::GetType() const {
    return "Oven";
}
