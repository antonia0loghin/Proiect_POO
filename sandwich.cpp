#include "sandwich.h"

Sandwich::Sandwich(): Product("Sandwich", 5, 6.5)
{
}

std::string Sandwich::GetCategory() const {
    return "Food";
}
std::string Sandwich::GetPreferredDeviceType() const {
    return "SandwichMaker";
}
