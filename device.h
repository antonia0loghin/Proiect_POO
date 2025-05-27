#pragma once
#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device {
protected:
    std::string m_name;
    int m_cooldown; // timp de așteptare până se poate folosi din nou

public:
    Device(std::string name, int cooldown);
    virtual ~Device();
    virtual void Use() = 0;
    std::string GetName() const;
    bool IsReady() const;
    virtual std::string GetType() const = 0;
};

#endif
