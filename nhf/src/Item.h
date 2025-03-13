#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include "memtrace.h"
using std::cout;
using std::endl;
using std::string;

class Item
{
protected:
    string name;
    int startingPrice;
    int currentBid;

public:
    Item(string n, int startPrice);
    virtual void displayItem() const;
    virtual ~Item() {}

    int getCurrentBid() const { return currentBid; }
    void setCurrentBid(int bid) { currentBid = bid; }
};

class Painting : public Item
{
private:
    string artist;

public:
    Painting(string n, int startPrice, string a);
    void displayItem() const override;
};

#endif
