#include "Auctioneer.h"

Auctioneer::Auctioneer(Item *i, Buyer **b, int count) : item(i), buyers(b), buyerCount(count) {}

EnglishAuctioneer::EnglishAuctioneer(Item *i, Buyer **b, int count) : Auctioneer(i, b, count) {}

void EnglishAuctioneer::startAuction()
{
    cout << "Auction started for: ";
    item->displayItem();

    int highestBid = item->getCurrentBid();
    Buyer *highestBidder = nullptr;

    for (int round = 0; round < 5; round++)
    {
        for (int i = 0; i < buyerCount; i++)
        {
            int bidAmount;
            if (buyers[i]->placeBid(highestBid, bidAmount))
            {
                highestBid = bidAmount;
                highestBidder = buyers[i];
                item->setCurrentBid(highestBid);
                cout << buyers[i]->getName() << " bids $" << highestBid << endl;
            }
        }
    }

    if (highestBidder)
    {
        cout << highestBidder->getName() << " wins the auction with $" << highestBid << "!" << endl;
    }
    else
    {
        cout << "No bids placed. Item not sold." << endl;
    }
}

void EnglishAuctioneer::declareWinner()
{
    cout << "Auction ended." << endl;
}
