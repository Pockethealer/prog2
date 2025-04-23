/**
 * @file Buyer.h
 * A vásárlók osztályait tartalmazó header file
 */
#ifndef BUYER_H
#define BUYER_H
#include "memtrace.h"
#include <iostream>

/**
 * A vásárló osztály absztrakt alaposztálya. Nem példányosítható.
 */
class Buyer
{
private:
    std::string name;
    double budget;
    double alreadySpent;

public:
    static double defBudget;
    Buyer(const std::string n, const double b) : name(n), budget(b), alreadySpent(0) {}
    virtual double placeBid(const double currentPrice, const double step) const = 0;
    /// @brief Kiírja az adott vásárlót, csak a teszteléshez kell.
    virtual void displayBuyer() const;
    /// @brief Hozzáadja a már elköltött pénzhez a kapott argumentumot
    /// @param i Ennyivel növeli a már elköltött pénz változó értékét
    virtual void addSpentMoney(const double i) { alreadySpent += i; }
    virtual double getSpentMoney() const { return alreadySpent; }
    virtual ~Buyer() {}
    std::string getName() const { return name; }
    double getBudget() const { return budget; }
    /// @brief Factory fv. a vásárlók példányosítására. Statikus hogy objektum nélkül is hívható legyen.
    /// @param name A vásáló neve
    /// @param budget A vásárló pénze
    /// @param aggressive Igaz ha agresszív buyert szeretnénk, később bővíthető integerré, ha több leszármazott van
    /// @return Pointer a létrehozott vásárló objektumra
    static Buyer *createBuyer(const std::string name, const double budget, const bool aggressive);
};
/**
 * A passzív vásárlót leíró osztály, visszafogottabban licitál
 */
class PassiveBuyer : public Buyer
{
public:
    PassiveBuyer(const std::string n, const double b) : Buyer(n, b) {}
    /// @brief Eldönti hogy licitál e az adott feltételek mellett, majd visszatér a feltett értékkel
    /// @param currentPrice Az eladási tárgy jelenlegi ára
    /// @param step A minimumm licitlépcső
    /// @return Visszatér a licit értékével, vagy 0-val ha nem licitál.
    double placeBid(const double currentPrice, const double step) const;
};
/**
 * Az agresszív vásárlót leíró osztály, nagyobbat és nagyobb eséllyel licitál
 */
class AggressiveBuyer : public Buyer
{
public:
    AggressiveBuyer(const std::string n, const int b) : Buyer(n, b) {}
    /// @brief Eldönti hogy licitál e az adott feltételek mellett, majd visszatér a feltett értékkel
    /// @param currentPrice Az eladási tárgy jelenlegi ára
    /// @param step A minimumm licitlépcső
    /// @return Visszatér a licit értékével, vagy 0-val ha nem licitál.
    double placeBid(const double currentPrice, const double step) const;
};

#endif
