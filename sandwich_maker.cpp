#include "sandwich_maker.h"
#include <iostream>

SandwichMaker::SandwichMaker() : Device("Sandwich Maker", 3, "Food") {}

void SandwichMaker::Use() {
    std::cout << "Preparing a delicious sandwich..." << std::endl;
    m_cooldown = 3;
}


