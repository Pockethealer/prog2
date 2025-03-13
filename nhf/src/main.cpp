#include <iostream>
#include <Windows.h>

#include "AuctionEvent.h"
#include "memtrace.h"
#include "gtest_lite.h"
using std::__cxx11::to_string;
int main()
{
    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);

    Item *painting = new Painting("Starry Night", 500, "Van Gogh");

    int buyerCount = 3;
    Buyer **buyers = new Buyer *[buyerCount];

    for (int i = 0; i < buyerCount; i++)
    {
        string name = "Buyer" + to_string(i + 1);
        int budget = (rand() % 500) + 800;
        buyers[i] = Buyer::createRandomBuyer(name, budget);
    }
    Auctioneer *auctioneer = new EnglishAuctioneer(painting, buyers, buyerCount);

    AuctionEvent event(painting, buyers, buyerCount, auctioneer);
    event.start();

    return 0;
}
