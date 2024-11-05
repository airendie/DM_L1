#ifndef UNIVERSUM_HPP
#define UNIVERSUM_HPP

#include <vector>

#include "binary_number.hpp"

using std::vector;

class Universum
{
    // m_bit_depth = n. max 31
    const u8 m_bit_depth;
    // Universum size = 2^n. Max: 2^31
    u64 m_size;
    // Vector of generated Gray's code for all arrays in Universum
    vector<BinaryNumber> m_gray_code;

public:
    /// @brief Конструктор
    /// @param n Разрядность универсума
    Universum(u8 n = 0);

    /// @brief Заполняет универсум числами по возрастанию, начиная с 0
    void generateIncrNumSeq();

    /// @brief Заполняет универсум кодом Грея
    void generateGrayCode();

    /// @brief Выводит содержимое универсума на экран
    void print() const;

    /// @brief Возвращает количество элементов в универсуме
    /// @return Размер вектора универсума
    u64 size() const;
    BinaryNumber operator[](u8 index) const;
};

#endif // end of unversum.hpp

