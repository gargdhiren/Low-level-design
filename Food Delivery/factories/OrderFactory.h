#ifndef ORDER_FACTORY
#define ORDER_FACTORY

#include <bits/stdc++.h>
#include "../modal/Cart.h"
#include "../modal/User.h"
#include "../modal/Restaurant.h"
#include "../modal/Order.h"
#include "../strategies/PayementStrategy.h"

using namespace std;

class OrderFactory
{
public:
    virtual Order *createOrder(User *user, Restaurant *res, PaymentStrategy *strategy, Cart *cart, string orderType, vector<MenuItem> items, double totalAmount) = 0;
};

#endif