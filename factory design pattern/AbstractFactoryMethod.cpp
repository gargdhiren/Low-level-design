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

class Fries
{
public:
    virtual void prepare() = 0;
};

class NormalPotatoFries : public Fries
{
public:
    void prepare() override
    {
        cout << "Prepare normal fries." << endl;
    }
};

class CheesyFries : public Fries
{
public:
    void prepare() override
    {
        cout << "Prepare cheesy fries." << endl;
    }
};

class PeriPeriFries : public Fries
{
public:
    void prepare() override
    {
        cout << "Prepare peri peri fries." << endl;
    }
};

class AirFriedFries : public Fries
{
public:
    void prepare() override
    {
        cout << "Prepare air fried fries." << endl;
    }
};

class MealFactory
{
public:
    virtual Burger *createBurger(string &type) = 0;
    virtual Fries *createFries(string &type) = 0;
};

class KingBurgerFactory : public MealFactory
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

    Fries *createFries(string &type)
    {
        if (type == "cheese")
        {
            return new CheesyFries();
        }
        else if (type == "normal")
        {
            return new NormalPotatoFries();
        }
        cout << "No such Fries." << endl;
        return NULL;
    }
};

class VeganBurgerFactory : public MealFactory
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

    Fries *createFries(string &type)
    {
        if (type == "airFried")
        {
            return new AirFriedFries();
        }
        else if (type == "PeriPeri")
        {
            return new PeriPeriFries();
        }
        cout << "No such Fries." << endl;
        return NULL;
    }
};

int main()
{
    string burgerType = "vegan";
    string friesType = "PeriPeri";
    MealFactory *veganBurgerFactory = new VeganBurgerFactory();
    Burger *burger = veganBurgerFactory->createBurger(burgerType);
    Fries *fries = veganBurgerFactory->createFries(friesType);
    if (burger)
        burger->prepare();
    if (fries)
        fries->prepare();

    string type1 = "nonVeg";
    string friesType1 = "normal";
    MealFactory *kingBurgerFactory = new KingBurgerFactory();
    Burger *burger1 = kingBurgerFactory->createBurger(type1);
    Fries *fries1 = kingBurgerFactory->createFries(friesType1);
    if (burger1)
        burger1->prepare();
    if (fries1)
        fries1->prepare();

    return 0;
}