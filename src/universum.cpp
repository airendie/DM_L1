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
        for (int j = 0; j < m_bit_depth; ++j)
        {
            int full_interval = 1 << (j + 2);
            int half_of_interval = 1 << (j + 1);
            int max_limit_of_current_interval = full_interval *
                    (1 + i / full_interval) - (1 << j);

            int center_of_current_interval =  max_limit_of_current_interval - half_of_interval;
            m_gray_code[i][j] = (i >= center_of_current_interval &&
                                 i < max_limit_of_current_interval);
            // std::cout << "j: " << j << '\n' << i << " is " <<
            //                 ((m_gray_code[i][j]) ? "behind " : "not behind ") <<
            //                 max_limit_of_current_interval <<
            //                   " and " << center_of_current_interval << '\n';
        }
    }
}

void Universum::print() const
{
    cout << "Universum: \n";

    if (m_bit_depth)
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

u64 Universum::size() const
{
    return m_size;
}

BinaryNumber Universum::operator[](u8 index) const
{
    try
    {
        if (index >= m_size)
            throw std::out_of_range("Exception: Out of range!");

        return m_gray_code[index];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return BinaryNumber();
}

// BinaryNumber &Universum::operator[](u8 index)
// {
//     try
//     {
//         if (index >= m_size)
//             throw std::out_of_range("Exception: Out of range!");

//         return m_gray_code[index];
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }
