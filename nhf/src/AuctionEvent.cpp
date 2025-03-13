#include "AuctionEvent.h"

AuctionEvent::AuctionEvent(Item *i, Buyer **b, int count, Auctioneer *a) : item(i), buyers(b), buyerCount(count), auctioneer(a) {}

void AuctionEvent::start()
{
    auctioneer->startAuction();
    auctioneer->declareWinner();
}

AuctionEvent::~AuctionEvent()
{
    delete item;
    delete auctioneer;
    for (int i = 0; i < buyerCount; i++)
        delete buyers[i];
    delete[] buyers;
}
