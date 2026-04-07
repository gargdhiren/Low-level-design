#include <bits/stdc++.h>
using namespace std;

class Burger
{
public:
    virtual void prepare() = 0;
};

class VegBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Prepare a veg burger." << endl;
    }
};

class NonVegBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Prepare a non-veg burger." << endl;
    }
};

class BurgerFactory
{
public:
    Burger *createBurger(string &type)
    {
        if (type == "veg")
        {
            return new VegBurger();
        }
        else if (type == "nonVeg")
        {
            return new NonVegBurger();
        }

        cout << "No such burger." << endl;
        return NULL;
    }
};

int main()
{
    string type = "veg";
    BurgerFactory *burgerFactory = new BurgerFactory();
    Burger *burger = burgerFactory->createBurger(type);
    burger->prepare();

    return 0;
}