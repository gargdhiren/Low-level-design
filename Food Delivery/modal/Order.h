#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>
#include "./User.h"
#include "../strategies/PayementStrategy.h"
#include "Restaurant.h"
#include "MenuItem.h"
using namespace std;

class Order
{
    static int nextOrderId;
    int orderId;
    User *user;
    PaymentStrategy *paymentStrategy;
    Restaurant *restaurant;
    double totalAmount;
    vector<MenuItem> items;
    string scheduled;

public:
    Order()
    {
        this->orderId = ++nextOrderId;
        restaurant = NULL;
        totalAmount = 0.0;
        user = NULL;
        paymentStrategy = NULL;
        scheduled = "";
    }

    void setUser(User *user)
    {
        this->user = user;
    }

    User *getUser()
    {
        return this->user;
    }

    void setRestaurant(Restaurant *res)
    {
        this->restaurant = res;
    }

    Restaurant *getRestaurant()
    {
        return this->restaurant;
    }

    void setPaymentStrategy(PaymentStrategy *strategy)
    {
        this->paymentStrategy = strategy;
    }

    bool payBill()
    {
        if (paymentStrategy)
        {
            paymentStrategy->pay(totalAmount);
            return true;
        }
        else
        {
            cout << "\nPayment failed. Select a pament strategy.\n";
            return false;
        }
    }

    void setItems(const vector<MenuItem> &its)
    {
        items = its;
        totalAmount = 0;
        for (auto &i : items)
        {
            totalAmount += i.getPrice();
        }
    }

    const vector<MenuItem> getItems()
    {
        return items;
    }

    void setScheduled(string s)
    {
        scheduled = s;
    }

    string getScheduled()
    {
        return scheduled;
    }

    double getTotal()
    {
        return totalAmount;
    }

    void setTotal(double total)
    {
        this->totalAmount = total;
    }

    int getOrderId()
    {
        return this->orderId;
    }

    virtual string getType() = 0;
};

int Order::nextOrderId = 0;

#endif