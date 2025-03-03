/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "allapotgep.h"
#include "memtrace.h"
/**
 * Állapotgép publikus interfésze.
 * A privát részt szabadon változtathatja, de a publikus részt ne változtassa, ne bővítse!
 */

bool Allapotgep::charToBool(char a)
{
    if (a == 'I' || a == 'i')
        return true;
    return false;
}

void Allapotgep::Allapot::setAllapot(bool a, std::string name)
{
    this->accepted = a;
    this->allapotName = name;
}

void Allapotgep::Allapot::setNext(int next, char a)
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

void Allapotgep::konfigural(const char *fajlnev)
{
    if (allapotok != nullptr)
    {
        alaphelyzet();
    }
    std::ifstream f(fajlnev);
    if (!f.is_open())
    {
        throw "EAS7U0";
    }
    std::string buffer;
    std::getline(f, buffer);
    allapotokSzama = std::stoi(buffer);
    aktualisAllapot = 0;
    bool accepted;
    std::string allapotnev;
    if (allapotok != nullptr)
    {
        delete[] allapotok;
    }
    allapotok = new Allapot[allapotokSzama];
    for (int i = 0; i < allapotokSzama; i++)
    {
        std::getline(f, buffer);
        allapotnev = buffer.substr(2);
        accepted = charToBool(buffer[0]);
        // std::cout << "Az állapot neve: " << allapotnev << " elfogadva:" << accepted << std::endl;
        allapotok[i].setAllapot(accepted, allapotnev);
        // std::cout << allapotok[i].accepted << allapotok[i].allapotName << std::endl;
    }
    /*sorokra for loop*/
    for (int i = 0; i < allapotokSzama; i++)
    {
        std::getline(f, buffer);
        std::istringstream stream(buffer);
        std::string token;
        /*oszlopokra for loop*/
        for (int j = 0; j < allapotokSzama; j++)
        {
            stream >> token;
            for (char a : token)
            {
                allapotok[i].setNext(j, a);
                // std::cout << "line:" << i + 1 << " Column " << j + 1 << ": " << a << std::endl;
            }
        }
    }
    f.close();
}

/** Visszaadja melyik állapot aktív.
 * @return pointer az aktív állapot nevére
 */
const char *Allapotgep::aktualisallapot()
{
    return allapotok[aktualisAllapot].allapotName.c_str();
}

/**
 * Elfogadó állapotban van-e az állapotgép.
 * @return true, ha elfogadó állapotban van
 */
bool Allapotgep::elfogad()
{
    return allapotok[aktualisAllapot].accepted;
}

/**
 * Az aktuális állapotnak és inputnak megfelelő következő állapotba léptet.
 * @param b - beérkező bázis, mint input
 */
void Allapotgep::atmenet(Bazis b)
{
    aktualisAllapot = allapotok[aktualisAllapot].nextState[b];
}

/**
 * Feldolgozza a paraméterként kapott bázissorozatot.
 * Visszaadja, hogy elfogadó állapotba került-e. (Nem áll vissza kezdő állapotba.)
 * @param b - input sorozatra mutató pointer
 * @param n - a sorozat hossza
 * @return tru, ha elfogadó állapotba került
 */
bool Allapotgep::feldolgoz(const Bazis *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        atmenet(b[i]);
    }
    return elfogad();
}

/**
 * Kezdő állapotba visz.
 */
void Allapotgep::alaphelyzet()
{
    if (allapotok != nullptr)
    {
        delete[] allapotok;
        allapotok = nullptr;
    }
    aktualisAllapot = 0;
    allapotokSzama = 0;
}
Allapotgep::~Allapotgep()
{
    alaphelyzet();
}
