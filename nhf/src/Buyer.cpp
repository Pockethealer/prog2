/**
 * @file Buyer.cpp
 * a vásárló osztályok függvényeit tartalmazó cpp file.
 */
#include "Buyer.h"

/// @brief A default budget érték a vásárllóknak
double Buyer::defBudget = 500;

void Buyer::displayBuyer() const
{
    std::cout << "Vásárló: " << name << " | Költségvetése: " << budget << std::endl;
}
Buyer *Buyer::createBuyer(std::string name, double budget, bool aggressive)
{
    if (aggressive)
        return new AggressiveBuyer(name + " (Agresszív)", budget);
    else
        return new PassiveBuyer(name + " (Passzív)", budget);
}

double PassiveBuyer::placeBid(double currentPrice, double step)
{
    int bidDeviation = currentPrice / 10; // a licitek szórása, konzervatív vásárlónál az ár 10%a
    if (bidDeviation == 0)                // Ha nulla lenne akkor később okozhat bugokat ezért van itt ez a safeguard
    {
        bidDeviation = 1;
    }
    double newBid = currentPrice + step + (std::rand() % bidDeviation); // az új licit értéke
    double remainingMoney = getBudget() - getSpentMoney();
    if (remainingMoney < newBid) // ha a licit nagyobb mint a maradék pénze akkor 0-val visszatér
    {
        return 0;
    }
    bool bid, weight = true;                   // Eldönti hogy licitáljon-e a jelenlegi ár alapján
    if ((getSpentMoney() / getBudget()) > 0.7) // ha a pénzének már több mint a 70%-át elköltötte akkor csak 20% eséllyel licitál, ami multiplikatív a következő esélyekkel.
    {
        weight = (rand() % 10 < 2);
    }
    if (remainingMoney * 0.3 > newBid) // ha a maradék pénzének a 20%ánál kevesebb a licit, akkor 70% eséllyel licitál
    {
        bid = (rand() % 10 < 7);
    }
    else if (remainingMoney * 0.5 > newBid) // ha a maradék pénzének a 50%ánál kevesebb a licit, akkor 40% eséllyel licitál
    {
        bid = (rand() % 10 < 4);
    }
    else // egyébként 20% eséllyel licitál
    {
        bid = (rand() % 10 < 2);
    }
    if (bid && weight) // ha a licit is igaz és a weight(ha a pénze nagy részét elköltötte akkor kicsi az esély hogy igaz) is igaz akkor visszatér a licittel
    {
        return newBid;
    }
    return 0; // egyébként visszatér nullával
}

double AggressiveBuyer::placeBid(double currentPrice, double step)
{
    int bidDeviation = currentPrice / 5; // a licitek szórása, agresszív vásárlónál az ár 20%a
    if (bidDeviation == 0)               // Ha nulla lenne akkor később okozhat bugokat ezért van itt ez a safeguard
    {
        bidDeviation = 1;
    }
    double newBid = currentPrice + step + (std::rand() % bidDeviation); // az új licit értéke
    double remainingMoney = getBudget() - getSpentMoney();
    if (remainingMoney < newBid) // ha a licit nagyobb mint a maradék pénze akkor 0-val visszatér
    {
        return 0;
    }
    if (getSpentMoney() != 0) // ha még nem vett semmit akkor mindenképpen licitál
    {
        return newBid;
    }
    bool bid;                          // Eldönti hogy licitáljon-e a jelenlegi ár alapján
    if (remainingMoney * 0.5 > newBid) // ha a maradék pénzének a 50%ánál kevesebb a licit, akkor 60% eséllyel licitál
    {
        bid = (rand() % 10 < 6);
    }
    else // egyébként 40% eséllyel licitál
    {
        bid = (rand() % 10 < 4);
    }
    if (bid) // ha a licit is igaz és a weight(ha a pénze nagy részét elköltötte akkor kicsi az esély hogy igaz) is igaz akkor visszatér a licittel
    {
        return newBid;
    }
    return 0;
}
