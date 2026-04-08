#ifndef UPI_PAYEMENT_STRATEGY
#define UPI_PAYEMENT_STRATEGY

#include "PayementStrategy.h"

class UPIPayementStrategy : public PaymentStrategy
{
    void pay(double amount) override
    {
        cout << "\nPayement of Rs." << amount << " done by UPI\n";
    }
};

#endif