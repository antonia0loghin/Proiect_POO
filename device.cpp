#include "device.h"
#include <iostream>

Device::Device(std::string name, int cooldown)
    : m_name(name), m_cooldown(cooldown) {
}

Device::~Device() {
    // Optional: logica pentru distrugere, dacă e cazul
}

std::string Device::GetName() const {
    return m_name;
}

bool Device::IsReady() const {
    return m_cooldown <= 0;
}
