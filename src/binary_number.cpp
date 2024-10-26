#include <iostream>
#include <stdexcept>

#include "binary_number.hpp"

using std::cout;

BinaryNumber::BinaryNumber(u64 number, u8 bit_depth)
{
    resize(bit_depth);
    setNumber(number);
}

// Очищает содержимое массива
void BinaryNumber::resize(u8 bit_depth)
{
    m_array.clear();

    m_size = bit_depth;

    for (int i = 0; i < m_size; ++i)
        m_array.push_front(0);
}

// Данная функция не меняет размера массиваы
void BinaryNumber::setNumber(u64 number)
{
    m_array.clear();

    // Изначально был цикл for. Пересмотрел структуру класса. Теперь здесь так.
    for (int i = 0; i < m_size; ++i)
    {
        m_array.push_front(number & 1);

        number = number >> 1;
    }
}

u8 &BinaryNumber::operator[](u8 index)
{
    try
    {
        if (index >= m_size)
            throw std::out_of_range("Exception: Out of range!");

        return m_array[index];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

u8 BinaryNumber::operator[](u8 index) const
{
    try
    {
        if (index >= m_size)
            throw std::out_of_range("Exception: Out of range!");

        return m_array[index];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void BinaryNumber::print()
{
    std::cout << m_array[7];
    // for (auto i = m_array.begin(); i != m_array.end(); ++i)
    //     std::cout << i;
}

u64 BinaryNumber::toUInt64() const
{
    u64 result = 0;

    for (int i = 0; i < m_size; ++i)
    {
        result |= m_array[i];
        if (i != m_size - 1)
            result = result << 1;
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num)
{
    for (int i = 0; i < bin_num.size(); ++i)
        os << bin_num[i];
    return os;
}
