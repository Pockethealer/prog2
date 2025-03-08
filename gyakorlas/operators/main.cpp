#include <iostream>
#include <Windows.h>

class Kordinata
{
    double x, y, z;
    std::string name;
    double value;

public:
    Kordinata();
    Kordinata(double x, double y, double z);
    Kordinata(double x, double y, double z, double value = 0);
    void pr()
    {
        std::cout << "A kordináta neve: " << this->name << "Kordinátái: " << x << y << z << " Értéke: " << value << std::endl;
    }
};

Kordinata::Kordinata()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->name = "First";
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    Kordinata a, b;
    a.pr();
    return 0;
}
