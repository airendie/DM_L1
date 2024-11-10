#ifndef BINARY_SET_HPP
#define BINARY_SET_HPP

#include <vector>

#include "binary_set.hpp"

using std::pair;
using std::vector;

// Класс мультимножества
class BinaryMultiset
{
    // Pointer to universum
    BinaryMultiset *m_universum;

    // m_bit_depth = n. max 31
    const u8 m_bit_depth;

    const u64 m_size;

    // Максимальная кратность элементов в мультимножестве
    const u32 m_max_occurrence_multiplicity;

    // Vector of generated Gray's code for all arrays in BinaryMultiset
    vector<pair<BinarySet, u64>> m_data;

public:
    /// @brief Конструктор
    BinaryMultiset(u8 bit_depth = 0, u32 max_occurrence_multiplicity = 0);
    BinaryMultiset(BinaryMultiset *universum);

    /// @brief Выводит содержимое универсума на экран
    void print() const;

    /// @brief Возвращает количество элементов в мультимножетсве
    /// @return Размер вектора мультимножетсва
    u64 size() const;

    /// @brief Возращает разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    u8 bit_depth() const;

    /// @brief Возращает саксимальную кратность вхождения элементов мультимножетсва
    /// @return Второй части пары <множество; число>
    u32 max_occurrence_multiplicity() const;
    pair<BinarySet, u64> operator[](u8 index) const;
};

/// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);

/// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);

#endif // end of binary_set.hpp
