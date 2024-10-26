#include <universum.hpp>
#include <iostream>

using std::cout;

Universum::Universum(u_int8_t n) : m_bit_depth{n}
{
    // if (m_bit_depth == 0)
    //     return;

    m_size = static_cast<int>(pow(2, n));
    m_gray_code.resize(m_size);

    for (int i = 0; i < m_size; ++i)
        m_gray_code[i].resize(m_bit_depth);
    
}

void Universum::print()
{
    cout << "Universum: \n";
    m_gray_code[0][10];
    for (int i = 0; i < m_size; ++i)
    {
        cout << i << ":  { " << m_gray_code[i] << " }\n";
    }
}
