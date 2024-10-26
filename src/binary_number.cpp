#include <iostream>
#include <stdexcept>

#include "binary_number.hpp"

using std::cout;

BinaryNumber::BinaryNumber(u8 n) : m_size{n}
{
    try
    {
        m_array.resize(m_size);
        if (m_array.empty())
            throw std::make_exception_ptr("Exception: Out of memory!");
        for (int i = 0; i < m_size; ++i)
            m_array.push_back(0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void BinaryNumber::resize(u8 new_size)
{
    try
    {
        m_array.clear();

        m_size = new_size;
        for (int i = 0; i < m_size; ++i)
            m_array.push_back(0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int &BinaryNumber::operator[](u8 index)
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

int BinaryNumber::operator[](u8 index) const
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
    for (int i = 0; i < m_size; ++i)
        std::cout << m_array[i];
}

std::ostream &operator<<(std::ostream &os, const BinaryNumber &bin_num)
{
    for (int i = 0; i < bin_num.size(); ++i)
        os << bin_num[i];
    return os;
}
