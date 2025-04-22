/**
 * @file Auction.cpp
 * Az aukció lebonyolításához szükséges függvények.
 */
#include "Auction.h"

void Auction::readFromFile(const char *file)
{
    std::ifstream f(file);
    if (!f.is_open())
    {
        throw std::runtime_error("Nem sikerült megnyitni a tárgyakat tartalmazó file-t!");
    }
    size_t ic;
    f >> ic;
    if (f.fail())
    {
        throw std::runtime_error("Nem sikerült kiolvasni a tárgyakat tartalmazó file-t!");
    }
    f.ignore(); // az újsor karaktert átugorja
    for (size_t i = 0; i < ic; i++)
    {
        std::string line;
        std::getline(f, line); // beolvassa az egész sort
        std::istringstream iss(line);
        std::string name;
        double price, step;

        if (!(iss >> name >> price >> step))
        {
            throw std::runtime_error("Helytelen beviteli formátum a:" + std::to_string(i + 1) + ". sorban");
        }
        items[i] = new Item(name, price, step);
    }
    itemCount = ic;
    f.close();
}
void Auction::startAuction(float agressiveRatio, size_t turnLimit, double budget)
{
    Buyer::defBudget = budget;
    size_t an = buyerCount * agressiveRatio; // Az agresszív vevők száma
    for (size_t i = 0; i < an; i++)
    {
        std::string name = "Buyer" + std::to_string(i + 1);
        buyers[i] = Buyer::createBuyer(name, Buyer::defBudget, true);
    }
    for (size_t i = an; i < buyerCount; i++)
    {
        std::string name = "Buyer" + std::to_string(i + 1);
        buyers[i] = Buyer::createBuyer(name, Buyer::defBudget, false);
    }
    /// Végigiterál a tárgyakon és mindegyiket elárverezi
    for (size_t i = 0; i < itemCount; i++)
    {
        auctionItem(items[i], turnLimit);
    }
}
void Auction::auctionItem(Item *item, size_t turnLimit)
{
    Buyer *winner = nullptr; // Pointer a győztesre, nullpointerre inicializélva
    double wp;               // Az aktuális körben az ár, a függvény végére az eladási ár
    double step = item->getStep();
    double currentHighest = item->getBasePrice(); // Az aktuális kör legmagasabb licitje
    int BidsPlaced = 2;                           // A licitek száma a körben, kettőre állítva, hogy be tudjon lépni az első loopba
    bool mask[buyerCount];                        // Tömb a kiesett vevők maszkolására
    for (size_t i = 0; i < buyerCount; i++)
    {
        mask[i] = true;
    }
    for (size_t i = 0; i < turnLimit && BidsPlaced >= 2; i++) // Külső loop a körökre
    {
        double bid;
        BidsPlaced = 0;                         // A kör elején nullára állítjuk a licitek számát
        for (size_t j = 0; j < buyerCount; j++) // Belső loop az adott körben végigiterálni a vevőkön.
        {
            if (mask[j] == true) // Ha kiesett a vevő akkor nem licitálhat
            {
                bid = buyers[j]->placeBid(wp, step);
                if (bid == 0) // Ha nem licitál akkor kiesik
                {
                    mask[j] = false;
                }
                else
                {
                    BidsPlaced++;             // Növeljük a számlálót
                    if (bid > currentHighest) // ha magasabb akkor feljegyezzük
                    {
                        currentHighest = bid;
                        winner = buyers[j];
                    }
                }
            }
            wp = currentHighest; // átállítjuk az aktuális árat a körben legmagasabb árra
        }
    }
    declareWinner(item, winner, wp);
}
void Auction::declareWinner(Item *i, Buyer *b, double finalPrice)
{
    if (b == nullptr) // Hibakezelés, ha nem kellt el a tárgy, akkor itt kezeljük, az eladási árnál -1 el jelezzük.
    {
        i->setWinner("Senki nem");
        i->setFinalPrice(-1);
        return;
    }
    i->setWinner(b->getName());
    i->setFinalPrice(finalPrice);
}
void Auction::writeToFile(const char *file, bool debug)
{
    std::ofstream f(file);
    std::ostream *output = &f;
    if (debug) // Ha a debug aktív az outputstream át van irányítva a cout-ra
    {
        output = &std::cout;
    }
    for (size_t i = 0; i < itemCount; i++)
    {
        (*output) << (*items[i]);
    }
    f.close();
}
Auction::~Auction()
{
    for (size_t i = 0; i < buyerCount; i++)
    {
        delete buyers[i];
    }
    for (size_t i = 0; i < itemCount; i++)
    {
        delete items[i];
    }
}
