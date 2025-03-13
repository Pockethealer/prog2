#include "Buyer.h"

Buyer::Buyer(string n, int b) : name(n), budget(b) {}

void Buyer::displayBuyer() const
{
    cout << "Buyer: " << name << " | Budget: $" << budget << endl;
}
Buyer *Buyer::createRandomBuyer(string name, int budget)
{
    int type = rand() % 2;

    if (type == 0)
        return new AggressiveBuyer(name + " (Agressive)", budget);
    else
        return new ConservativeBuyer(name + " (Passive)", budget);
}

ConservativeBuyer::ConservativeBuyer(string n, int b) : Buyer(n, b) {}

bool ConservativeBuyer::placeBid(int currentPrice, int &bidAmount)
{
    if (budget > currentPrice && rand() % 10 < 3)
    { // 30% chance
        bidAmount = currentPrice + (rand() % 20 + 5);
        return true;
    }
    return false;
}

AggressiveBuyer::AggressiveBuyer(string n, int b) : Buyer(n, b) {}

bool AggressiveBuyer::placeBid(int currentPrice, int &bidAmount)
{
    if (budget > currentPrice && rand() % 10 < 7)
    {
        bidAmount = currentPrice + (rand() % 50 + 10);
        return true;
    }
    return false;
}
