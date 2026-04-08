#ifndef USER_H
#define USER_H

#include "bits/stdc++.h"
#include "../modal/Cart.h"
using namespace std;

class User
{
    int userId;
    string name;
    static int nextUserId;
    Cart *cart;
    string location;

public:
    User(string name, string location)
    {
        userId = ++nextUserId;
        this->name = name;
        this->location = location;
        cart = new Cart();
    }

    string getName()
    {
        return this->name;
    }

    string getLocation()
    {
        return this->location;
    }

    Cart *getCart()
    {
        return cart;
    }
};

int User::nextUserId = 0;

#endif