/**
 * @file Auction.h
 * Az aukció osztály deklarációját tartalmazó header file.
 */
#ifndef AUCTION_H
#define AUCTION_H
#include "memtrace.h"
#include "Item.h"
#include "Buyer.h"
#include "hetero_store.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
/**
 * Az aukció lebonyolításáért felelős singleton osztály, heterogén kollekcióban tartalmazza az a Buyer classokat.
 */
class Auction
{
private:
    HeteroStore<Item> items;
    HeteroStore<Buyer> buyers; // Ősosztály pointert tárolok
    /// @brief Explicit megtiltott másoló konstruktor
    Auction(Auction &);
    /// @brief Explicit megtiltott assignment operator
    Auction &operator=(Auction &);
    /// @brief Konstruktor, beállítja a vevők számát, privát, hogy ne lehessen véletlenül példányosítani, tárgyak számát 0-ra inicializálja
    /// @param bcount A vevők száma
    Auction() {}

public:
    /// @brief Függvény az Auction sigleton egyetlen statikus példányának létrehozására
    /// @param b A vevők száma amivel inicializáljuk
    /// @return Visszatér a statikus példány referenciájával
    static Auction &getInstance()
    {
        static Auction instance;
        return instance;
    }
    /// @brief Beolvassa a file-ból az eladni kívánt termékeket, és az items tömbbe rakja
    /// @param debug Flag, ha be van kapcsolva file helyett a konzolról olvassa be az adatokat, alapértelmezetten hamis
    /// @param file A file amiből beolvas alapértelmezetten az items.txt ugyanebben a könyvtárban
    void readFromFile(const bool debug = false, const char *file = "items.txt");
    /// @brief Generál vevőket majd elárverezi a tárgyakat.
    /// @param turnLimit A maximális körök száma
    /// @param agressiveRatio Az agresszív vevők aránya a passzívokhoz képest, 0 és 1 közötti szám
    /// @param budget Az alapértelmezett budget értéket állítja be
    /// @param buyerCount A vevők számát állítja be
    void startAuction(const float agressiveRatio, const size_t turnLimit, const double budget, const size_t buyerCount);
    /// @brief Adott tárgyat elárverez
    /// @param i Pointer a tárgyra
    /// @param turnLimit A beállított maximum körök száma
    void auctionItem(Item *item, const size_t turnLimit);
    /// @brief Bejegyzi az Item osztály objektumába az eladási árat, és a vevő nevét
    /// @param i Az adott tárgy
    /// @param b A vevőre mutató
    /// @param finalPrice  A végső eladási ár
    void declareWinner(Item *i, Buyer *b, const double finalPrice);
    /// @brief Kiírja file-ba vagy stdoutra a tárgyakat a nyertesekkel és végső árral együtt.
    /// @param file A file neve ahova írja, alapértelmezetten itemsSold.txt
    /// @param debug Flag, ha be van kapcsolva file helyett a konzolra írja ki az eredményeket, alapértelmezetten igaz
    void writeToFile(const bool debug = true, const char *file = "itemsSold.txt");
    /// @brief Destruktor, mivel a tároló kezeli a foglalt terület felszabadítását így itt nem kell
    ~Auction() {}
    /// @brief Takarító fv. ha manuálisan akarjuk a memóriát törölni
    void AuctionClear()
    {
        items.clear();
        buyers.clear();
    }
};

#endif
