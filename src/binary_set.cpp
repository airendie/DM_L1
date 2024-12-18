#include <iostream>
#include <stdexcept>

#include "binary_set.hpp"

using std::cout;

BinarySet::BinarySet(u64 number, u8 bit_depth)
{
    resize(bit_depth);
    setNumber(number);
}

// Очищает содержимое массива
void BinarySet::resize(u8 bit_depth)
{
    m_array.clear();

    m_size = bit_depth;

    for (int i = 0; i < m_size; ++i)
        m_array.push_front(0);
}

// Данная функция не меняет размера массиваы
void BinarySet::setNumber(u64 number)
{
    m_array.clear();

    // Изначально был цикл for. Пересмотрел структуру класса. Теперь здесь так.
    for (int i = 0; i < m_size; ++i)
    {
        m_array.push_front(number & 1);

        number = number >> 1;
    }
}

BinarySet &BinarySet::operator!()
{
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = m_array[i] ^ 1;
    }
    return *this;
}

bool BinarySet::operator<(const BinarySet &other) const
{
    return (toUInt64() < other.toUInt64());
}

bool BinarySet::operator==(const BinarySet &other) const
{
    if (m_size == other.size())
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_array[i] != other.m_array[i])
                return false;
        }
        return true;
    }
    return false;
}

bool BinarySet::operator!=(const BinarySet &other) const
{
    if (m_size == other.size())
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_array[i] != other.m_array[i])
                return true;
        }
        return false;
    }
    return true;
}

u8 &BinarySet::operator[](size_t index)
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

    return m_array[0];
}

u8 BinarySet::operator[](size_t index) const
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

    return m_array[0];
}

void BinarySet::print()
{
    for (int i = 0; i < m_size; ++i)
        std::cout << (int)m_array[i];
}

u64 BinarySet::toUInt64() const
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

std::ostream &operator<<(std::ostream &os, const BinarySet &bin_num)
{
    for (int i = 0; i < bin_num.size(); ++i)
        os << (unsigned)bin_num[i];
    return os;
}
