#ifndef DINE_IN_ORDER_H
#define DINE_IN_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"

using namespace std;

class DineInOrder : public Order
{
    string restaurantAddress;

public:
    DineInOrder()
    {
        restaurantAddress = "";
    }
    void setAddress(string add)
    {
        restaurantAddress = add;
    }

    string getAddress()
    {
        return this->restaurantAddress;
    }

    string getType() override
    {
        return "DineInOrder";
    }
};

#endif