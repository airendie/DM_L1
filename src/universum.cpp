#include <universum.hpp>
#include <iostream>

using std::cout;

Universum::Universum(u_int8_t n) : m_bit_depth{n}
{
    m_size = (u_int64_t)1 << n;
    m_gray_code.resize(m_size);

    for (int i = 0; i < m_size; ++i)
    {
        m_gray_code[i].resize(m_bit_depth);
    }
}

void Universum::generateIncrNumSeq()
{
    for (int i = 0; i < m_size; ++i)
        m_gray_code[i].setNumber(i);
}

void Universum::generateGrayCode()
{
    // По массивам
    for (int i = 0; i < m_size; ++i)
    {
        int a;
        // Последний разряд
    }
}

void Universum::print()
{
    cout << "Universum: \n";

    if (m_size)
    {
        for (int i = 0; i < m_size; ++i)
        {
            cout << i << ":  { " << m_gray_code[i] << " }\n";
        }
    }
    else
    {
        cout << "0: ∅\n";
    }
}
