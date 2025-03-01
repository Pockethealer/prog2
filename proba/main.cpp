/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>
#include <cstring>

enum Bazis
{
    Adenin,
    Citozin,
    Guanin,
    Timin
};
inline Bazis cast(char b)
{
    std::locale loc;
    char k = std::tolower(b, loc);
    Bazis ret;
    switch (k)
    {
    case 'a':
        ret = Adenin;
        break;
    case 'c':
        ret = Citozin;
        break;
    case 'g':
        ret = Guanin;
        break;
    case 't':
        ret = Timin;
        break;
    default:
        throw "Format!!";
        break;
    }
    return ret;
}
inline char cast(Bazis b, bool upper = true)
{
    char ret = '0';
    switch (b)
    {
    case Adenin:
        ret = 'a';
        break;
    case Citozin:
        ret = 'c';
        break;
    case Guanin:
        ret = 'g';
        break;
    case Timin:
        ret = 't';
        break;
    }
    if (upper)
    {
        std::locale loc;
        ret = std::toupper(ret, loc);
    }
    return ret;
}

class Allapot
{
    bool accepted;
    std::string allapotName;
    Allapot(bool a, std::string name)
    {
        this->accepted = a;
        this->allapotName = name;
    }
    int nextState[4];
};
bool charToBool(char a)
{
    if (a == 'I' || a == 'i')
        return true;
    return false;
}

int main(void)
{
    std::ifstream f("paros.txt");
    std::string buffer;
    std::getline(f, buffer);
    // std::cout << buffer << std::endl;
    int n = std::stoi(buffer);
    std::cout << n << std::endl;
    bool accepted;
    std::string allapotnev;
    Allapot allapotok[n];
    for (int i = 0; i < n; i++)
    {
        std::getline(f, buffer);
        allapotnev = buffer.substr(2);
        accepted = charToBool(buffer[0]);
        std::cout << "Az állapot neve: " << allapotnev << " elfogadva:" << accepted << std::endl;
        allapotok[i] = new Allapot(accepted, allapotnev);
    }
}