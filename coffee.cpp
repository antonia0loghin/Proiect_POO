#include "coffee.h"

Coffee::Coffee()
    : Product("Coffee", 3, 4.0) // name, cook_time, price
{
}
Coffee::Coffee(const std::string& name, double price, int cook_time)
    : Product(name, price, cook_time) {
}

std::string Coffee::GetCategory() const {
    return "Drink";
}
std::string Coffee::GetPreferredDeviceType() const {
    return "CoffeePot";
}

