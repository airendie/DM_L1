#ifndef BINARY_SET_HPP
#define BINARY_SET_HPP

#include <vector>
#include <set>
#include "binary_set.hpp"

using std::pair;
using std::set;
using std::vector;

#define DEFAULT_MAX_OCCURRENCE_MULTIPLICITY 1000

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
    set<BinaryMultiset &> m_subsets;

    // !TODO Сделать обновление (добавление/удаление) списка детей и кластерное удаление!!!!!!!!!!!!!

    // Количество элементов в бинарном множестве
    u8 m_bit_depth;

    // Количество различных элементов в мультимножестве
    u64 m_size;

    // Максимальная кратность элементов в мультимножестве
    u64 m_max_occurrence_multiplicity;

    // Множество пар из указателей на множество в универсуме и
    // их количества в конкретном мультимножетсве
    vector<pair<BinarySet *, u64>> m_data;

public:
    /// @brief Конструктор универсума
    /// @param bit_depth Количество элементов в бинарных массиах
    /// @param max_occurrence_multiplicity Максимальная разрядность в мультимножестве
    BinaryMultiset(u8 bit_depth = 0, u64 max_occurrence_multiplicity = 0);
    /// @brief Конструктор мультимножества как подмножества универсума
    /// @param universum Родительский универсум. От него наследуются все параметры.
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
    u64 max_occurrence_multiplicity() const;

    /// @brief Возращает разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    vector<pair<BinarySet *, u64>> &data();

    pair<BinarySet *, u64> operator[](u8 index) const;

    ~BinaryMultiset() { clear(); };

private:
    void addToUniversumSubsets();
    void removefromUniversumSubsets();
};

/// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);
BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth,
                                                 u64 max_occurrence_multiplicity =
                                                     DEFAULT_MAX_OCCURRENCE_MULTIPLICITY);

/// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
BinaryMultiset generateGrayCode(u8 bit_depth,
                                u64 max_occurrence_multiplicity =
                                    DEFAULT_MAX_OCCURRENCE_MULTIPLICITY);

#endif // end of binary_set.hpp

