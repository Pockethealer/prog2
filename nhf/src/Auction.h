/**
 * @file Auction.h
 * Az aukció osztály deklarációját tartalmazó header file.
 */
#ifndef AUCTION_H
#define AUCTION_H
#include "memtrace.h"
#include "Item.h"
#include "Buyer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
/**
 * Az aukció lebonyolításáért felelős singleton osztály, heterogén kollekcióban tartalmazza az a Buyer classokat.
 */
class Auction
{
protected:
    Item *items[30];
    size_t itemCount;
    Buyer *buyers[30]; // ősosztály pointert tárolok
    size_t buyerCount;
    /// @brief explicit megtiltott másoló konstruktor
    Auction(Auction &);
    /// @brief explicit megtiltott assignment operator
    Auction &operator=(Auction &);
    /// @brief Konstruktor, beállítja a vevők számát, privát, hogy ne lehessen véletlenül példányosítani
    /// @param bcount A vevők száma, alapértelmezetten 5
    Auction(size_t bcount = 5) : buyerCount(bcount) {}

public:
    /// @brief Függvény az Auction sigleton egyetlen statikus példányának létrehozására
    /// @param b A vevők száma amivel inicializáljuk
    /// @return Visszatér a statikus példány referenciájával
    static Auction &getInstance(double b)
    {
        static Auction instance(b);
        return instance;
    }
    /// @brief beolvassa a file-ból az eladni kívánt termékeket, és az items tömbbe rakja
    /// @param file a file amiből beolvas alapértelmezetten az items.txt ugyanebben a könyvtárban
    void readFromFile(const char *file = "items.txt");
    /// @brief Generál vevőket majd elárverezi a tárgyakat.
    /// @param turnLimit A maximális körök száma, alapértelmezetten 5
    /// @param agressiveRatio Az agresszív vevők aránya a passzívokhoz képest, 0 és 1 közötti szám, alapértelmezetten 1
    /// @param budget Az alapértelmezett budget értéket állítja be, alapértelmezetten 500
    void startAuction(float agressiveRatio = 1.0, size_t turnLimit = 5, double budget = 500);
    /// @brief Adott tárgyat elárverez
    /// @param i Pointer a tárgyra
    /// @param turnLimit A beállított maximum körök száma
    void auctionItem(Item *item, size_t turnLimit);
    /// @brief Bejegyzi az Item osztály objektumába az eladási árat, és a vevő nevét
    /// @param i Az adott tárgy
    /// @param b A vevőre mutató
    /// @param finalPrice  A végső eladási ár
    void declareWinner(Item *i, Buyer *b, double finalPrice);
    /// @brief Kiírja file-ba vagy stdoutra a tárgyakat a nyertesekkel és végső árral együtt.
    /// @param file A file neve ahova írja, alapértelmezetten itemsSold.txt
    /// @param debug Flag, ha be van kapcsolva file helyett a konzolra írja ki az eredményeket, alapértelmezetten igaz
    void writeToFile(const char *file = "itemsSold.txt", bool debug = true);
    /// @brief Destruktor, felszabadítja a lefoglalt memóriát
    ~Auction();
};

#endif
