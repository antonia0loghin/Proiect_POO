#include "device.h"

Device::Device(const std::string& name, int cooldown, const std::string& category)
    : m_name(name), m_cooldown(0), m_compatible_category(category) {
}

std::string Device::GetName() const {
    return m_name;
}

std::string Device::GetCompatibleCategory() const {
    return m_compatible_category;
}

bool Device::IsReady() const {
    return m_cooldown <= 0;
}

void Device::Tick() {
    if (m_cooldown > 0) {
        --m_cooldown;
    }
}
