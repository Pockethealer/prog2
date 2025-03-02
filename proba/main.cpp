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
#include <sstream>

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
public:
    bool accepted;
    std::string allapotName;

    void setAllapot(bool a, std::string name)
    {
        this->accepted = a;
        this->allapotName = name;
    }
    /* 1: adenin, 2:citozin, 3: guanin, 4: timin*/
    int nextState[4];
    void setNext(int next, char a)
    {
        switch (a)
        {
        case 'A':

            this->nextState[0] = next;
            break;

        case 'C':

            this->nextState[1] = next;
            break;

        case 'G':

            this->nextState[2] = next;
            break;

        case 'T':

            this->nextState[3] = next;
            break;
        default:
            break;
        }
    }
    void allapotKiir(void)
    {
        std::cout << "Az állapot neve: " << this->allapotName << " elfogadva:" << this->accepted << std::endl;
        std::cout << "Az állapotból Adenin hatására a " << this->nextState[0] + 1 << ". állapotba lép." << std::endl;
        std::cout << "Az állapotból Citozin hatására a " << this->nextState[1] + 1 << ". állapotba lép." << std::endl;
        std::cout << "Az állapotból Guanin hatására a " << this->nextState[2] + 1 << ". állapotba lép." << std::endl;
        std::cout << "Az állapotból Timin hatására a " << this->nextState[3] + 1 << ". állapotba lép." << std::endl;
    }
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
        // std::cout << "Az állapot neve: " << allapotnev << " elfogadva:" << accepted << std::endl;
        allapotok[i].setAllapot(accepted, allapotnev);
        // std::cout << allapotok[i].accepted << allapotok[i].allapotName << std::endl;
    }
    /*sorokra for loop*/
    for (int i = 0; i < n; i++)
    {
        std::getline(f, buffer);
        std::istringstream stream(buffer);
        std::string token;
        /*oszlopokra for loop*/
        for (int j = 0; j < n; j++)
        {
            stream >> token;
            for (char a : token)
            {
                allapotok[i].setNext(j, a);
                // std::cout << "line:" << i + 1 << " Column " << j + 1 << ": " << a << std::endl;
            }
        }
        allapotok[i].allapotKiir();
    }
}