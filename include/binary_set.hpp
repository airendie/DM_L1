#ifndef BINARY_NUMBER_HPP
#define BINARY_NUMBER_HPP

#include <iostream>
#include <deque>

#include "def.hpp"

using std::deque;

// Дилемма:
// Для генерации кода Грея удобнее использовать структуру, при которой
// в соответствующем по индексу бите хранится та же степень двойки
// N: { 0, 1, 1, 1 }
// i:   0  1  2  3
// Но для вывода удобнее, когда все наоборот...
//

// Класс бинарного массива
class BinarySet
{
    // max 31
    u8 m_size;

    //
    deque<u8> m_array{0};

public:
    /// @brief Конструктор
    /// @param number Число, которое будет представлено в двоичном виде
    /// @param bit_depth Разрядность (количество разрядов)
    BinarySet(u64 number = 0, u8 bit_depth = 8);

    void resize(u8 new_size);
    void setNumber(u64 number);

    BinarySet &operator!();

    bool operator==(const BinarySet&) const;
    bool operator!=(const BinarySet&) const;

    u8 &operator[](size_t index);
    u8 operator[](size_t index) const;

    u8 size() const { return m_size; }
    void print();

    u64 toUInt64() const;

    friend std::ostream &operator<<(std::ostream &os, const BinarySet &bin_num);
};

std::ostream &operator<<(std::ostream &os, const BinarySet &bin_num);

#endif // end of binary_number.hpp
