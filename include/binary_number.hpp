#ifndef BINARY_NUMBER_HPP
#define BINARY_NUMBER_HPP

#include <iostream>
#include <deque>

#include "def.hpp"

using std::deque;

class BinaryNumber
{
    // max 31
    u8 m_size;

    // Gray's Code
    deque<u8> m_array{0};

public:
    /// @brief Конструктор
    /// @param number Число, которое будет представлено в двоичном виде
    /// @param bit_depth Разрядность (количество разрядов)
    BinaryNumber(u64 number = 0, u8 bit_depth = 8);

    void resize(u8 new_size);
    void setNumber(u64 number);


    u8 &operator[](u8 index);
    u8 operator[](u8 index) const;

    u8 size() const { return m_size; }
    void print();

    u64 toUInt64() const;

    friend std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num);
};

std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num);

#endif // end of binary_number.hpp
