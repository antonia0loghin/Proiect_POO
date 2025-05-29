#include "sandwich.h"

Sandwich::Sandwich()
    : Product( "Food", 6.5, 5) {
}

Sandwich::Sandwich(const std::string& name, double price, int cook_time)
    : Product(name,  price, cook_time) {
}

std::string Sandwich::GetCategory() const {
    return "Food";
}
std::string Sandwich::GetPreferredDeviceType() const {
    return "SandwichMaker";
}
