#include "coffee.h"

Coffee::Coffee()
    : Product("Coffee", 3, 4.0) // name, cook_time, price
{
}

std::string Coffee::GetCategory() const {
    return "Drink";
}
std::string Coffee::GetPreferredDeviceType() const {
    return "CoffeePot";
}

