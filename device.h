#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
protected:
    std::string m_name;
    std::string m_compatible_category;
    int m_cooldown;

public:
    Device(const std::string& name, int cooldown, const std::string& category);
    virtual ~Device() {}

    virtual void Use() = 0;

    std::string GetName() const;
    std::string GetCompatibleCategory() const;
    bool IsReady() const;
    void Tick();
};

#endif
