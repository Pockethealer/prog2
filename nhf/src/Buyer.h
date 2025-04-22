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
    double alreadySpent = 0;

public:
    static double defBudget;
    Buyer(std::string n, double b) : name(n), budget(b) {}
    virtual double placeBid(double currentPrice, double step) = 0;
    /// @brief Kiírja az adott vásárlót, csak a teszteléshez kell.
    virtual void displayBuyer() const;
    /// @brief hozzáadja a már elköltött pénzhez a kapott argumentumot
    /// @param i ennyivel növeli a már elköltött pénz változó értékét
    virtual void addSpentMoney(double i) { alreadySpent += i; }
    virtual double getSpentMoney() { return alreadySpent; }
    virtual ~Buyer() {}
    std::string getName() const { return name; }
    double getBudget() const { return budget; }
    /// @brief Factory fv. a vásárlók példányosítására. Statikus hogy objektum nélkül is hívható legyen.
    /// @param name a vásáló neve
    /// @param budget a vásárló pénze
    /// @return pointer a létrehozott vásárló objektumra
    static Buyer *createBuyer(std::string name, double budget, bool aggressive);
};
/**
 * A passzív vásárlót leíró osztály, visszafogottabban licitál
 */
class PassiveBuyer : public Buyer
{
public:
    PassiveBuyer(std::string n, double b) : Buyer(n, b) {}
    /// @brief eldönti hogy licitál e az adott feltételek mellett, majd visszatér a feltett értékkel
    /// @param currentPrice az eladási tárgy jelenlegi ára
    /// @param step a minimumm licitlépcső
    /// @return visszatér a licit értékével, vagy 0-val ha nem licitál.
    double placeBid(double currentPrice, double step);
};
/**
 * Az agresszív vásárlót leíró osztály, nagyobbat és nagyobb eséllyel licitál
 */
class AggressiveBuyer : public Buyer
{
public:
    AggressiveBuyer(std::string n, int b) : Buyer(n, b) {}
    /// @brief eldönti hogy licitál e az adott feltételek mellett, majd visszatér a feltett értékkel
    /// @param currentPrice az eladási tárgy jelenlegi ára
    /// @param step a minimumm licitlépcső
    /// @return visszatér a licit értékével, vagy 0-val ha nem licitál.
    double placeBid(double currentPrice, double step);
};

#endif
