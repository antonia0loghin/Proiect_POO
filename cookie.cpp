#include "cookie.h"

Cookie::Cookie()
    : Product( "Dessert", 3.0, 2) {
}
Cookie::Cookie(const std::string& name, double price, int cook_time)
    : Product("Dessert", price, cook_time) {
}

std::string Cookie::GetCategory() const {
    return "Dessert";
}
std::string Cookie::GetPreferredDeviceType() const {
    return "Oven";
}
