/**
 * @file Item.h
 * Az aukcióra bocsájtott tárgyak osztájának leírása, az alapvető függvényeivel.
 * Mivel a függvények rövidek, és egyértelműek ezért nem csináltam hozzá külön cpp file-t.
 */
#ifndef ITEM_H
#define ITEM_H
#include "memtrace.h"
#include <iostream>

/// @brief Az eladott tárgyak osztálya
class Item
{
protected:
    std::string name;
    double basePrice;
    double minIncrement;
    std::string winner;
    double finalPrice;

public:
    /// @brief Konstruktor az Item classhoz
    /// @param n A tárgy neve
    /// @param startPrice A kezdő értéke
    /// @param minIncrement A minimum licitlépcső
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
    std::string getName() const { return name; }
    /// @brief Standard getter fv.
    double getBasePrice() const { return basePrice; }
    /// @brief Standard getter fv.
    double getStep() const { return minIncrement; }
    /// @brief Standard getter fv.
    std::string getWinner() const { return winner; }
    /// @brief Standard getter fv.
    double getFinalPrice() const { return finalPrice; }
    /// @brief Standard setter fv.
    void setWinner(const std::string s) { winner = s; }
    /// @brief Standard setter fv.
    void setFinalPrice(const double p) { finalPrice = p; }
};
/**
 * Kiírja az adott eladási tárgyat output streamre.
 */
inline std::ostream &operator<<(std::ostream &os, const Item &i)
{
    os << i.getName() << " tárgyat " << i.getWinner() << " nyerte, "
       << i.getFinalPrice() << " leütési áron." << std::endl;
    return os;
}

#endif
