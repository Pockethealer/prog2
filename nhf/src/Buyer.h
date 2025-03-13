#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "memtrace.h"
using std::cout;
using std::endl;
using std::string;

class Buyer
{
protected:
    string name;
    int budget;

public:
    Buyer(string n, int b);
    virtual bool placeBid(int currentPrice, int &bidAmount) = 0;
    virtual void displayBuyer() const;
    virtual ~Buyer() {}

    string getName() const { return name; }
    static Buyer *createRandomBuyer(string name, int budget);
};

class ConservativeBuyer : public Buyer
{
public:
    ConservativeBuyer(string n, int b);
    bool placeBid(int currentPrice, int &bidAmount) override;
};

class AggressiveBuyer : public Buyer
{
public:
    AggressiveBuyer(string n, int b);
    bool placeBid(int currentPrice, int &bidAmount) override;
};

#endif
