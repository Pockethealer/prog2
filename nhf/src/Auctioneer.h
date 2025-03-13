#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "Item.h"
#include "Buyer.h"
#include "memtrace.h"

class Auctioneer
{
protected:
    Item *item;
    Buyer **buyers;
    int buyerCount;

public:
    Auctioneer(Item *i, Buyer **b, int count);
    virtual void startAuction() = 0;
    virtual void declareWinner() = 0;
    virtual ~Auctioneer() {}
};

class EnglishAuctioneer : public Auctioneer
{
public:
    EnglishAuctioneer(Item *i, Buyer **b, int count);
    void startAuction() override;
    void declareWinner() override;
};

#endif
