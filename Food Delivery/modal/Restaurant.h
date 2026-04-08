#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <bits/stdc++.h>
#include "MenuItem.h"
using namespace std;

class Restaurant
{
    int id;
    string name;
    string location;
    vector<MenuItem> menu;
    static int nextRestaurantId;

public:
    Restaurant(string name, string location)
    {
        this->id = ++nextRestaurantId;
        this->name = name;
        this->location = location;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void setName(int name)
    {
        this->name = name;
    }

    void setLocation(int location)
    {
        this->location = location;
    }

    int getId()
    {
        return this->id;
    }

    string getName()
    {
        return this->name;
    }

    string getLocation()
    {
        return this->location;
    }

    void addMenuItem(MenuItem item)
    {
        menu.push_back(item);
    }

    vector<MenuItem> getMenu()
    {
        return this->menu;
    }
};

int Restaurant::nextRestaurantId = 0;

#endif
