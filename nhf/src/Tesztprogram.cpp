/**
 * @file Tesztprogram.cpp
 * Tesztprogram az elkészített funkciók tesztelésére
 */
#include "memtrace.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Auction.h"
#include "gtest_lite.h"
#include <cstring>

void paramBeolvas()
{
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // konzol karakterkódolás beállítása, csak windowson.
#endif
    int seed = time(0);                        // seed beállítása, alapértelmezetten az idővel seedel
    srand(seed);                               // seedelés
    size_t buyerCount = 30;                    // globális paraméter: a vevők száma, default 30, max 30
    double defBudget = 500;                    // globális paraméter: a a vevők pénze, default 500
    size_t turnLimit = 10;                     // globális paraméter: a körök számának limitje, default 10
    float aggressiveRatio = 1.0;               // globális paraméter: az agresszív vevők aránya az összes vevőhöz képest 0-1 közötti szám, default 1
    Auction &auction = Auction::getInstance(); // singleton inicializálás

    /**
     * Tesztek:
     */
    TEST(Buyer, variables)
    {
        Buyer *b1 = Buyer::createBuyer("BuyerTest", 1500, 1);
        EXPECT_EQ(1500, b1->getBudget()) << "== Nem jo Budget! ***\n";
        EXPECT_STREQ("BuyerTest (Agresszív)", b1->getName().c_str()) << "== Nem jo a buyer nev! ***\n";
        b1->addSpentMoney(50);
        EXPECT_EQ(50, b1->getSpentMoney()) << "== Nem jo Spent money fv.! ***\n";
        Buyer *bp = Buyer::createBuyer("BuyerTest", 1500, false);
        EXPECT_STREQ("BuyerTest (Passzív)", bp->getName().c_str()) << "== Nem jo a factory fv.! ***\n";
        delete b1;
        delete bp;
    }
    ENDM

    TEST(Buyer, behaviour)
    {
        Buyer *b2 = Buyer::createBuyer("BuyerTest", 1500, true);
        bool licital = true;
        for (size_t i = 0; i < 200 && licital; i++)
        {
            if (b2->placeBid(200, 50) == 0)
                licital = false;
        }
        EXPECT_TRUE(licital) << "== Nem licital mindig az agressziv vevo! ==\n";
        delete b2;
    }
    ENDM

    TEST(Item, variables)
    {
        Item i1("Proba1", 200, 30);
        EXPECT_EQ(200, i1.getBasePrice()) << "== Nem jo kezdo ertek! ***\n";
        EXPECT_EQ(30, i1.getStep()) << "== Nem jo az increment! ***\n";
        EXPECT_STREQ("Proba1", i1.getName().c_str()) << "== Nem jo az item nev! ***\n";
        i1.setFinalPrice(400);
        i1.setWinner("John");
        EXPECT_EQ(400, i1.getFinalPrice()) << "== Nem jo az increment! ***\n";
        EXPECT_STREQ("John", i1.getWinner().c_str()) << "== Nem jo az item nev! ***\n";
    }
    ENDM

    TEST(Auction, input)
    {
        // A mesterséges input
        std::istringstream input("2\nPhone 300 50\nLaptop 200 100\n");
        /// Lecseréljük az input buffert és elmentjük a régit
        std::streambuf *old = std::cin.rdbuf(input.rdbuf());
        /// Lefuttatjuk a tesztet
        EXPECT_NO_THROW(auction.readFromFile(true)) << "Nem sikerult beolvasni adatokat\n";
        /// Visszaállítjuk a régi inputbuffert
        std::cin.rdbuf(old);
        /// 2.teszt
        std::istringstream input2("3\nCamera 500 50\nYoyo 30 10\nBoardgame 10 2\n");
        old = std::cin.rdbuf(input2.rdbuf());
        EXPECT_NO_THROW(auction.readFromFile(true)) << "Nem sikerult masodjara adatot beolvasni\n";
        std::cin.rdbuf(old);
        /// 3.teszt
        std::istringstream input3("33\nCamera 500 50\nYoyo 30 10\nBoardgame 10 2\n");
        old = std::cin.rdbuf(input3.rdbuf());
        try
        {
            auction.readFromFile(true);
            FAIL() << "Nem erkezett az elvart std::out_of_range exception\n";
        }
        catch (const std::out_of_range &e)
        {
            SUCCEED();
        }
        std::cin.rdbuf(old);
        auction.AuctionClear();
    }
    ENDM
    TEST(Auction, output)
    {
        /// A mesterséges input
        std::istringstream input("1\nCamera 600 50");
        std::streambuf *old = std::cin.rdbuf(input.rdbuf());
        EXPECT_NO_THROW(auction.readFromFile(true)) << "Nem sikerult beolvasni adatokat\n";
        std::cin.rdbuf(old);
        EXPECT_NO_THROW(auction.startAuction(aggressiveRatio, turnLimit, defBudget, buyerCount)) << "Nem futott a startAuction fv.\n";
        std::ostringstream output;
        std::streambuf *oldout = std::cout.rdbuf(output.rdbuf());
        EXPECT_NO_THROW(auction.writeToFile(true)) << "Nem sikerult kiirni az adatokat\n";
        std::cout.rdbuf(oldout);
        std::string op = output.str();
        EXPECT_STREQ("Camera tárgyat senki nem nyerte, -1 leütési áron.\n", op.c_str()) << "Nem jo az output!\n";
        /// Takaritas
        auction.AuctionClear();
    }
    ENDM

    TEST(auction, logic) // A vásárlások eloszlása 30 emberre
    {
        srand(3);           // Külön seed a determinisztikus viselkedéshez
        size_t cases = 200; // Az esetszám beállítása, a nagyobb pontosság érdekében magasabbat érdemes
        Item itest1("Teszt", 20, 10);
        /// Generálunk vevőket, a paraméterek fixek a determinisztikus tesztelésért
        auction.startAuction(0.5, 10, 50000, 30);
        /// Tömb a vevőknek, a 0. helyen azt számolom hányszor nem kellt el
        double winners[31];
        for (size_t i = 0; i < 30; i++)
        {
            winners[i] = 0;
        }
        size_t winner;
        size_t start;
        size_t len;
        // Egy sűrűségfüggvényt csinálok a winners tömbbe, hogy melyik vevő milyen gyakran nyert
        for (size_t i = 0; i < cases; i++)
        {
            auction.auctionItem(&itest1, 10);
            std::string winnerStr = itest1.getWinner();
            start = 5;
            len = 0;
            winner = 0;
            while (std::isdigit(winnerStr[start + len]))
            {
                ++len;
            }
            if (len != 0)
            {
                winner = std::stoi(winnerStr.substr(start, len));
            }
            winners[winner]++;
        }
        /// Súlyozom az esetek számával
        for (size_t i = 0; i < 30; i++)
        {
            winners[i] = winners[i] / cases;
        }
        EXPECT_FLOAT_EQ(0.04, winners[1]) << "Nem determinisztikus a teszteles!";
        /// A licitálási szabályok finomhangolásához debug printer
        /* for (size_t i = 0; i < 30; i++)
        {
            std::cout << winners[i] << std::endl;
        } */
        /// Takaritas
        auction.AuctionClear();
        /// Az eredeti seed visszaállítása
        srand(seed);
    }
    ENDM

        if (!gtest_lite::test.fail())
    {
        std::cout << "\nMinden Teszt megfelelt" << std::endl;
    }
    /**
     * Egy próba aukció bemutatása:
     */
    try
    {
        auction.readFromFile();                                                  // beolvasás
        auction.startAuction(aggressiveRatio, turnLimit, defBudget, buyerCount); // A tárgyak elárverezése
    }
    catch (const std::exception &e) // Input parsing, filekezelési és memory allocation hibák fordulhatnak elő
    {
        std::cerr << "Hiba: " << e.what() << '\n';
    }
    auction.writeToFile(0); // Az árverés eredményének kiírása az itemsSold.txt tile-ba.
    return 0;
}
