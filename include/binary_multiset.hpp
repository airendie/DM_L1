#ifndef BINARY_SET_HPP
#define BINARY_SET_HPP

#include <vector>

#include "binary_set.hpp"

using std::pair;
using std::vector;

// Класс мультимножества
class BinaryMultiset
{
    // Указатель на универсальное множество
    // Если мультимножество "верхнее" в иерархии,
    // указатель на универсум будет пустым.
    // При уничтожении универсума, очищаются и его "дети"
    BinaryMultiset *m_universum;

    // Массив адресов мультимножеств,
    // для которых данное мультимножество является универсумом.
    vector<BinarySet &> m_subsets;

    // !TODO Сделать обновление (добавление/удаление) списка детей и кластерное удаление!!!!!!!!!!!!!

    // Количество элементов в бинарном множестве
    u8 m_bit_depth;

    // Количество различных элементов в мультимножестве
    u64 m_size;

    // Максимальная кратность элементов в мультимножестве
    u32 m_max_occurrence_multiplicity;

    // Множество пар из указателей на множество в универсуме и
    // их количества в конкретном мультимножетсве
    vector<pair<BinarySet *, u64>> m_data;

public:
    /// @brief Конструктор
    BinaryMultiset(u8 bit_depth = 0, u32 max_occurrence_multiplicity = 0);
    BinaryMultiset(BinaryMultiset *universum);

    BinaryMultiset &operator=(const BinaryMultiset &other);
    BinaryMultiset &operator=(BinaryMultiset &&other);

    void clear();

    bool operator==(const BinaryMultiset &other) const;

    bool operator!=(const BinaryMultiset &other) const;

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
BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);

/// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
BinaryMultiset generateGrayCode(u8 bit_depth);

#endif // end of binary_set.hpp
