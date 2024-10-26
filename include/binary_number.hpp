#ifndef BINARY_NUMBER_HPP
#define BINARY_NUMBER_HPP

#include <iostream>
#include <vector>

#include "def.hpp"

using std::vector;

class BinaryNumber
{
    // max 31
    u8 m_size;

    // Gray's Code
    vector<int> m_array{0};

public:
    BinaryNumber() : m_size{0}{}
    BinaryNumber(u8 n);

    void resize(u8 new_size);

    int &operator[](u8 index);
    int operator[](u8 index) const;

    u8 size() const { return m_size; }
    void print();

    friend std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num);
};

std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num);

#endif // end of binary_number.hpp
