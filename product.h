#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
protected:
    std::string m_name;
    int m_cook_time;
    double m_price;
	std::string m_category;

public:
    Product(std::string name = "Unknown", int cookTime = 0, double price = 0.0);
    virtual ~Product();

    virtual void Print() const;
    virtual std::string GetCategory() const = 0;

    int GetCookTime() const;
    double GetPrice() const;
    std::string GetName() const;

    // Overload operator <<
    friend std::ostream& operator<<(std::ostream& out, const Product& p);
    virtual std::string GetPreferredDeviceType() const = 0;

};

#endif
