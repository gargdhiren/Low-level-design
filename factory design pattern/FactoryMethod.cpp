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

class VeganBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Prepare a vegan burger." << endl;
    }
};

class GlutenFreeBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Prepare a gluten free burger." << endl;
    }
};

class BurgerFactory
{
public:
    virtual Burger *createBurger(string &type) = 0;
};

class KingBurgerFactory : public BurgerFactory
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

class VeganBurgerFactory : public BurgerFactory
{
public:
    Burger *createBurger(string &type)
    {
        if (type == "vegan")
        {
            return new VeganBurger();
        }
        else if (type == "glutenFree")
        {
            return new GlutenFreeBurger();
        }

        cout << "No such burger." << endl;
        return NULL;
    }
};

int main()
{
    string type = "vegan";
    BurgerFactory *veganBurgerFactory = new VeganBurgerFactory();
    Burger *burger = veganBurgerFactory->createBurger(type);
    burger->prepare();

    string type1 = "nonVeg";
    BurgerFactory *kingBurgerFactory = new KingBurgerFactory();
    Burger *burger1 = kingBurgerFactory->createBurger(type1);
    burger1->prepare();

    return 0;
}