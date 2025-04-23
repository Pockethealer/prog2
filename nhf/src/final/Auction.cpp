/**
 * @file Auction.cpp
 * Az aukció lebonyolításához szükséges függvények.
 */
#include "Auction.h"

void Auction::readFromFile(const bool debug, const char *file)
{
    std::ifstream f(file);
    if (!f.is_open())
    {
        throw std::runtime_error("Nem sikerült megnyitni a tárgyakat tartalmazó file-t!");
    }
    std::istream *input = &f;
    if (debug) // Ha a debug aktív az inputstream át van irányítva a cin-re
    {
        input = &std::cin;
    }
    size_t ic = 0; // Az újonnan hozzáadott tárgyak száma
    *input >> ic;
    if (input->fail() || (input->eof()))
    {
        throw std::runtime_error("Nem sikerült kiolvasni a tárgyakat tartalmazó fileból a tárgyak számát!");
    }
    if (ic + items.size() > items.capacity())
    {
        throw std::out_of_range("Túl sok tárgyat próbál meg beolvasni!");
    }

    input->ignore(); // az újsor karaktert átugorja
    for (size_t i = 0; i < ic; i++)
    {
        std::string line;
        if (!std::getline(*input, line))
        {
            throw std::runtime_error("Nem sikerült beolvasni a " + std::to_string(i + 1) + ". sort");
        }
        std::istringstream iss(line);
        std::string name;
        double price, step;

        if (!(iss >> name >> price >> step)) // Nem lehet space a tárgy nevében
        {
            throw std::runtime_error("Helytelen beviteli formátum a:" + std::to_string(i + 1) + ". sorban");
        }
        items.add(new Item(name, price, step));
    }
    f.close();
}
void Auction::startAuction(const float agressiveRatio, const size_t turnLimit, const double budget, const size_t buyerCount)
{
    Buyer::defBudget = budget;
    size_t an = buyerCount * agressiveRatio; // Az agresszív vevők száma
    for (size_t i = 0; i < an; i++)
    {
        std::string name = "Buyer" + std::to_string(i + 1);
        buyers.add(Buyer::createBuyer(name, Buyer::defBudget, true));
    }
    for (size_t i = an; i < buyerCount; i++)
    {
        std::string name = "Buyer" + std::to_string(i + 1);
        buyers.add(Buyer::createBuyer(name, Buyer::defBudget, false));
    }
    /// Végigiterál a tárgyakon és mindegyiket elárverezi
    for (size_t i = 0; i < items.size(); i++)
    {
        auctionItem(items[i], turnLimit);
    }
}
void Auction::auctionItem(Item *item, const size_t turnLimit)
{
    Buyer *winner = nullptr;                         // Pointer a győztesre, nullpointerre inicializélva
    double currentRoundPrice = item->getBasePrice(); // Az aktuális körben közben a legmagasabb ár
    double step = item->getStep();
    double previousRoundHighest = currentRoundPrice; // Az előző kör legmagasabb licitje
    int BidsPlaced = buyers.size();                  // A licitek száma a körben
    bool mask[buyers.size()];                        // Tömb a kiesett vevők maszkolására
    for (size_t i = 0; i < buyers.size(); i++)
    {
        mask[i] = true;
    }
    for (size_t i = 0; i < turnLimit && BidsPlaced >= 2; i++) // Külső loop a körökre
    {
        double bid;
        BidsPlaced = 0;                            // A kör elején nullára állítjuk a licitek számát
        for (size_t j = 0; j < buyers.size(); j++) // Belső loop az adott körben végigiterálni a vevőkön.
        {
            if (!mask[j])
            {
                continue; // A kiesett vásálókat átugorja
            }
            bid = buyers[j]->placeBid(previousRoundHighest, step);
            if (bid == 0) // Ha nem licitál akkor kiesik
            {
                mask[j] = false;
            }
            else
            {
                BidsPlaced++;                // Növeljük a számlálót
                if (bid > currentRoundPrice) // ha magasabb akkor feljegyezzük
                {
                    currentRoundPrice = bid;
                    winner = buyers[j];
                }
            }
        }
        previousRoundHighest = currentRoundPrice; // átállítjuk az aktuális árat a körben legmagasabb árra
    }
    declareWinner(item, winner, previousRoundHighest);
}
void Auction::declareWinner(Item *i, Buyer *b, const double finalPrice)
{
    if (b == nullptr) // Hibakezelés, ha nem kellt el a tárgy, akkor itt kezeljük, az eladási árnál -1 el jelezzük.
    {
        i->setWinner("senki nem");
        i->setFinalPrice(-1);
        return;
    }
    b->addSpentMoney(finalPrice);
    i->setWinner(b->getName());
    i->setFinalPrice(finalPrice);
}
void Auction::writeToFile(const bool debug, const char *file)
{
    std::ofstream f(file);
    if (!f.is_open())
    {
        throw std::runtime_error("Nem sikerült megnyitni az eladott tárgyakat tartalmazó file-t!");
    }
    std::ostream *output = &f;
    if (debug) // Ha a debug aktív az outputstream át van irányítva a cout-ra
    {
        output = &std::cout;
    }
    for (size_t i = 0; i < items.size(); i++)
    {
        (*output) << (*items[i]);
    }
    if (!debug)
    {
        std::cout << "Sikeresen kiírva " << items.size() << "db tárgy file-ba!" << std::endl;
    }

    f.close();
}
