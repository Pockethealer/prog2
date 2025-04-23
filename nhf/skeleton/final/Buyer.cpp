/**
 * @file Buyer.cpp
 * A vásárló osztályok függvényeit tartalmazó cpp file.
 */
#include "Buyer.h"

/// @brief A default budget érték a vásárlóknak, egyszer inicializálva, hogy utána az Auction class elérje
double Buyer::defBudget = 500;

void Buyer::displayBuyer() const
{
    std::cout << "Vásárló: " << name << " | Költségvetése: " << budget << std::endl;
}
