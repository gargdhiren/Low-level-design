#ifndef MENUITEM_H
#define MENUITEM_H

#include <bits/stdc++.h>
using namespace std;

class MenuItem
{
private:
    int id;
    string name;
    double price;

public:
    MenuItem(int id, string name, double price)
    {
        this->id = id;
        this->name = name;
        this->price = price;
    }

    int getId()
    {
        return this->id;
    }

    string getName()
    {
        return this->name;
    }

    double getPrice()
    {
        return this->price;
    }
};

#endif