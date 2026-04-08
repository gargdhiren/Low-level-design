#ifndef CART_H
#define CART_H

#include <bits/stdc++.h>
#include "Restaurant.h"
using namespace std;

class Cart
{
    Restaurant *restaurant;
    double totalPrice;
    vector<MenuItem> items;

public:
    Cart()
    {
        this->restaurant = NULL;
        totalPrice = 0.0;
    }

    void setRestaurant(Restaurant *r)
    {
        this->restaurant = r;
    }

    Restaurant *getRestaurant()
    {
        return this->restaurant;
    }

    double getTotalPrice()
    {
        return this->totalPrice;
    }

    void addToCart(MenuItem item)
    {
        if (!this->restaurant)
        {
            cout << "\nNo restaurant is set. Kindly set the restaurant first.\n";
            return;
        }
        totalPrice += item.getPrice();
        items.push_back(item);
    }

    //was causing problems
    // void removeFromCart(MenuItem item)
    // {
    //     if (!this->restaurant)
    //     {
    //         cout << "\nNo restaurant is set. Kindly set the restaurant first.\n";
    //         return;
    //     }

    //     auto it = find(items.begin(), items.end(), item);

    //     if (it == items.end())
    //     {
    //         cout << "\nDish " << item.getName() << " is not present in the cart.\n";
    //     }
    //     else
    //     {
    //         totalPrice -= item.getPrice();
    //         items.erase(it);
    //     }
    // }

    vector<MenuItem> getItemsInCart()
    {
        if (items.size() == 0)
        {
            cout << "\nNo dishes added to cart. Kindly add dishes.\n";
        }
        return items;
    }

    bool isEmpty()
    {
        return !this->restaurant && items.size() == 0;
    }

    void clear()
    {
        items.clear();
        restaurant = nullptr;
    }
};

#endif