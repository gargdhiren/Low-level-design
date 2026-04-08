#ifndef SCHEDULED_ORDER_FACTORY
#define SCHEDULED_ORDER_FACTORY

#include <bits/stdc++.h>
#include "OrderFactory.h"
#include "../modal/DineInOrder.h"
#include "../modal/TakeAwayOrder.h"
#include "../utils/TimeUtils.h"
using namespace std;

class ScheduledOrderFactory : public OrderFactory
{
private:
    string scheduledTime;

public:
    ScheduledOrderFactory(string scheduleTime)
    {
        this->scheduledTime = scheduleTime;
    }

    Order *createOrder(User *user, Restaurant *res, PaymentStrategy *strategy, Cart *cart, string orderType, vector<MenuItem> items, double totalAmount) override
    {
        Order *order;
        if (orderType == "DineInOrder")
        {
            auto dineInOrder = new DineInOrder();
            dineInOrder->setAddress(res->getLocation());
            order = dineInOrder;
        }
        else
        {
            auto takeAwayOrder = new TakeAwayOrder();
            takeAwayOrder->setAddress(user->getLocation());
            order = takeAwayOrder;
        }
        order->setUser(user);
        order->setRestaurant(res);
        order->setPaymentStrategy(strategy);
        order->setItems(items);
        order->setTotal(totalAmount);
        order->setScheduled(this->scheduledTime);

        return order;
    }
};

#endif