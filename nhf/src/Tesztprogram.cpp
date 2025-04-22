/**
 * @file Tesztprogram.cpp
 * Tesztprogram az elkészített funkciók tesztelésére
 */
#include "memtrace.h"
#include <iostream>
#include <Windows.h>
#include "Auction.h"
#include "gtest_lite.h"
int main()
{
    srand(time(0));              // seedelés
    SetConsoleOutputCP(CP_UTF8); // utf-8 beállítás a konzolra
    int buyerCount = 5;          // vevők számának beállítása
    try
    {
        Auction &a = Auction::getInstance(buyerCount); // initialize singleton
        a.readFromFile();                              // read item data
        a.startAuction();                              // A tárgyak elárverezése
        a.writeToFile();                               // Az árverés eredményének kiírása
    }
    catch (const std::exception &e)
    {
        std::cerr << "Hiba: " << e.what() << '\n';
    }

    return 0;
}
