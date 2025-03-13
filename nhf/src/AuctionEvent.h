#ifndef AUCTIONEVENT_H
#define AUCTIONEVENT_H

#include "Auctioneer.h"
#include "memtrace.h"

class AuctionEvent
{
private:
    Item *item;
    Buyer **buyers;
    int buyerCount;
    Auctioneer *auctioneer;

public:
    AuctionEvent(Item *i, Buyer **b, int count, Auctioneer *a);
    void start();
    ~AuctionEvent();
};

#endif
