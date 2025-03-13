#include <iostream>
#include <Windows.h>

class Kordinata
{
    double x, y, z;
    std::string name;
    double value;

public:
    Kordinata();
    Kordinata(double x, double y, double z, double value = 0);
    Kordinata operator+(const Kordinata &k) const;
    Kordinata operator+(double k) const;

    void pr() const
    {
        std::cout << "A kordináta neve: " << this->name << "Kordinátái: " << x
                  << " " << y << " " << z << " Értéke: " << value << std::endl;
    }
};

Kordinata::Kordinata()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->name = "First";
}
Kordinata::Kordinata(double x, double y, double z, double value)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->name = "First";
    this->value = value;
}
Kordinata Kordinata::operator+(const Kordinata &k) const
{
    return Kordinata(this->x + k.x, this->y + k.y, this->z + k.z, this->value + k.value);
}

Kordinata Kordinata::operator+(double k) const
{
    return Kordinata(this->x + k, this->y, this->z, this->value);
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    const Kordinata a(1, 2, 3, 10);
    Kordinata b(1, 2, 3, 10);
    Kordinata c = a + b;
    c.pr();
    return 0;
}
