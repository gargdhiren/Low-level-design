#ifndef TAKE_AWAY_ORDER_H
#define TAKE_AWAY_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"

using namespace std;

class TakeAwayOrder : public Order
{
    string userAddress;

public:
    TakeAwayOrder()
    {
        userAddress = "";
    }
    void setAddress(string add)
    {
        userAddress = add;
    }

    string getAddress()
    {
        return this->userAddress;
    }

    string getType() override
    {
        return "TakeAwayOrder";
    }
};

#endif