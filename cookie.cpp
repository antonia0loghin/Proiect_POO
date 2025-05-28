#include "cookie.h"

Cookie::Cookie(): Product("Cookie", 2, 2.0)
{
}

std::string Cookie::GetCategory() const {
    return "Dessert";
}
std::string Cookie::GetPreferredDeviceType() const {
    return "Oven";
}
