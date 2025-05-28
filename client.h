#ifndef CLIENT_H
#define CLIENT_H

#include "order.h"

class Client {
private:
    std::string m_name;
    Order m_order;
    int m_patience_seconds = 10;

public:
    Client(std::string name, int order_id);
    void PrintClientInfo() const;
    Order& GetOrder() ;
    std::string GetName() const;

    void DecreasePatience();
    bool IsStillWaiting() const;
};

#endif
