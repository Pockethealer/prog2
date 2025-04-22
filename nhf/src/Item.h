/**
 * @file Item.h
 * Az aukcióra bocsájtott tárgyak osztájának leírása, az alapvető függvényeivel.
 * Mivel a függvények rövidek, és egyértelműek ezért nem csináltam hozzá külön cpp file-t.
 */
#ifndef ITEM_H
#define ITEM_H
#include "memtrace.h"
#include <iostream>

/**
 * @class Item
 *
 * Az aukció során eladott tárgyak osztálya
 *
 */
class Item
{
protected:
    std::string name;
    double basePrice;
    double minIncrement;
    std::string winner;
    double finalPrice;

public:
    Item(std::string n, double startPrice, double minIncrement) : name(n), basePrice(startPrice), minIncrement(minIncrement) {}

    Item(const Item &i) : name(i.name), basePrice(i.basePrice), minIncrement(i.minIncrement) {}
    Item &operator=(const Item &i)
    {
        if (this != &i)
        {
            name = i.name;
            basePrice = i.basePrice;
            minIncrement = i.minIncrement;
        }
        return *this;
    }

    /// @brief Standard getter fv.
    std::string getName() { return name; }
    /// @brief Standard getter fv.
    double getBasePrice() { return basePrice; }
    /// @brief Standard getter fv.
    double getStep() { return minIncrement; }
    /// @brief Standard getter fv.
    std::string getWinner() { return winner; }
    /// @brief Standard getter fv.
    double getFinalPrice() { return finalPrice; }
    /// @brief Standard setter fv.
    void setWinner(std::string s) { winner = s; }
    /// @brief Standard setter fv.
    void setFinalPrice(double p) { finalPrice = p; }
};
/**
 * Kiírja az adott eladási tárgyat output streamre.
 */
inline std::ostream &operator<<(std::ostream &os, Item &i)
{
    os << i.getName() << " tárgyat " << i.getWinner() << " nyerte, "
       << i.getFinalPrice() << " leütési áron." << std::endl;
    return os;
}

#endif
