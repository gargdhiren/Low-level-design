#ifndef TOMATO_APP_H
#define TOMATO_APP_H

#include <vector>
#include <string>
#include "modal/User.h"
#include "modal/Restaurant.h"
#include "modal/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PayementStrategy.h"
#include "strategies/UPIPayementStrategy.h"
#include "strategies/CODPayementStrategy.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduledOrderFactory.h"
#include "services/NotificationService.h"
#include "utils/TimeUtils.h"
using namespace std;

class TomatoApp
{

public:
    TomatoApp()
    {
        initializeRestaurants();
    }

    void initializeRestaurants()
    {
        Restaurant *restaurant1 = new Restaurant("Bikaner", "Delhi");
        restaurant1->addMenuItem(MenuItem(1, "Chole Bhature", 120));
        restaurant1->addMenuItem(MenuItem(2, "Samosa", 15));

        Restaurant *restaurant2 = new Restaurant("Haldiram", "Kolkata");
        restaurant2->addMenuItem(MenuItem(2, "Raj Kachori", 80));
        restaurant2->addMenuItem(MenuItem(2, "Pav Bhaji", 100));
        restaurant2->addMenuItem(MenuItem(3, "Dhokla", 50));

        Restaurant *restaurant3 = new Restaurant("Saravana Bhavan", "Chennai");
        restaurant3->addMenuItem(MenuItem(1, "Masala Dosa", 90));
        restaurant3->addMenuItem(MenuItem(2, "Idli Vada", 60));
        restaurant3->addMenuItem(MenuItem(3, "Filter Coffee", 30));

        RestaurantManager *restaurantManager = RestaurantManager::getInstance();
        restaurantManager->addRestaurant(restaurant1);
        restaurantManager->addRestaurant(restaurant2);
        restaurantManager->addRestaurant(restaurant3);

        // Add other sample restaurants...
    }

    vector<Restaurant *> searchRestaurants(string location)
    {
        return RestaurantManager::getInstance()->getRestaurantsByLocation(location);
    }

    void selectRestaurant(User *user, Restaurant *restaurant)
    {
        Cart *cart = user->getCart();
        cart->setRestaurant(restaurant);
    }

    void addToCart(User *user, int itemCode)
    {
        Restaurant *restaurant = user->getCart()->getRestaurant();
        if (!restaurant)
        {
            cout << "Please select a restaurant first." << endl;
            return;
        }
        for (auto item : restaurant->getMenu())
        {
            if (item.getId() == itemCode)
            {
                user->getCart()->addToCart(item);
                break;
            }
        }
    }

    Order *checkoutNow(User *user, const string orderType, PaymentStrategy *paymentStrategy)
    {
        return checkout(user, orderType, paymentStrategy, new NowOrderFactory());
    }

    Order *checkoutScheduled(User *user, string orderType, PaymentStrategy *paymentStrategy, string scheduleTime)
    {
        return checkout(user, orderType, paymentStrategy, new ScheduledOrderFactory(scheduleTime));
    }

    Order *checkout(User *user, string orderType, PaymentStrategy *paymentStrategy, OrderFactory *orderFactory)
    {
        if (user->getCart()->isEmpty())
            return nullptr;

        Cart *userCart = user->getCart();
        Restaurant *orderedRestaurant = userCart->getRestaurant();
        vector<MenuItem> itemsOrdered = userCart->getItemsInCart();
        double totalCost = userCart->getTotalPrice();

        Order *order = orderFactory->createOrder(user, orderedRestaurant, paymentStrategy, userCart, orderType, itemsOrdered, totalCost);
        OrderManager::getInstance()->addOrder(order);
        return order;
    }

    void payForOrder(User *user, Order *order)
    {
        bool isPaymentSuccess = order->payBill();

        // clear user cart if payment is successful.
        if (isPaymentSuccess)
        {
            NotificationService *notification = new NotificationService();
            notification->notify(order);
            // user->getCart()->clear();
        }
    }

    void printUserCart(User *user)
    {
        cout << "Items in cart:" << endl;
        cout << "------------------------------------" << endl;
        for (auto item : user->getCart()->getItemsInCart())
        {
            cout << item.getId() << " : " << item.getName() << " : ₹" << item.getPrice() << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Grand total : ₹" << user->getCart()->getTotalPrice() << endl;
    }
};

#endif