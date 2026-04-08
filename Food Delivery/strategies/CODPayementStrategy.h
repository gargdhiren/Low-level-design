#ifndef COD_PAYEMENT_STRATEGY
#define COD_PAYEMENT_STRATEGY

#include "PayementStrategy.h"

class CODPayementStrategy : public PaymentStrategy
{
    void pay(double amount) override
    {
        cout << "\nPayement of Rs." << amount << " done by cash\n";
    }
};

#endif