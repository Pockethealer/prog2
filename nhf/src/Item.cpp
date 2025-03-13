#include "Item.h"

Item::Item(string n, int startPrice) : name(n), startingPrice(startPrice), currentBid(startPrice) {}

void Item::displayItem() const
{
    cout << "Item: " << name << " | Starting Price: $" << startingPrice << " | Current Bid: $" << currentBid << endl;
}

Painting::Painting(string n, int startPrice, string a) : Item(n, startPrice), artist(a) {}

void Painting::displayItem() const
{
    cout << "Painting by " << artist << ": " << name << " | Starting Price: $" << startingPrice << " | Current Bid: $" << currentBid << endl;
}
