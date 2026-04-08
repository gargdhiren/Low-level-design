#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include <bits/stdc++.h>
#include "../modal/Restaurant.h"

using namespace std;

class RestaurantManager
{
    vector<Restaurant *> restaurants;
    static RestaurantManager *instance;

    RestaurantManager()
    {
        // for singleton class
    }

public:
    static RestaurantManager *getInstance()
    {
        if (instance == NULL)
        {
            instance = new RestaurantManager();
        }

        return RestaurantManager::instance;
    }

    void addRestaurant(Restaurant *res)
    {
        restaurants.push_back(res);
    }

    vector<Restaurant *> getRestaurants()
    {
        return this->restaurants;
    }

    vector<Restaurant *> getRestaurantsByLocation(string location)
    {
        vector<Restaurant *> filteredRestaurants;
        for (auto res : restaurants)
        {
            if (res->getLocation() == location)
            {
                filteredRestaurants.push_back(res);
            }
        }

        if (filteredRestaurants.size() == 0)
        {
            cout << "\nNo restaurants found for location " << location << endl;
        }

        return filteredRestaurants;
    }
};

RestaurantManager *RestaurantManager::instance = NULL;

#endif