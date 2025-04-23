/**
 * \file: hetero_store.hpp
 * Az órai gyakorlaton elkészített tároló felhasználása a nagyháziban.
 *
 */

#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

#include "memtrace.h"
#include <iostream>
#include <stdexcept>

/// @brief A gyakorlaton készített tároló templát
/// @tparam T A tárolandó class neve
/// @tparam e Az error típusa
/// @tparam s A tároló kapacitása, alapértelmezetten 30
template <class T, size_t s = 30, class e = std::out_of_range>
class HeteroStore
{
    T *data[s];
    size_t siz;
    size_t cap;
    HeteroStore(HeteroStore &);
    HeteroStore &operator+(const HeteroStore &);

public:
    HeteroStore() : siz(0), cap(s) {}
    size_t size() const { return siz; }
    size_t capacity() const { return cap; }
    void add(T *p)
    {
        if (siz >= cap)
        {
            delete p;
            throw e("Túllépi a megadott kapacitást!");
        }
        data[siz++] = p;
    }
    template <typename F>
    void traverse(F f)
    {
        for (size_t i = 0; i < siz; i++)
            f(data[i]);
    }
    void clear()
    {
        for (size_t i = 0; i < siz; i++)
            delete data[i];
        siz = 0;
    }
    T *operator[](size_t i) const
    {
        return data[i];
    }
    ~HeteroStore() { clear(); }
};

#endif // HETEROSTORE_HPP
