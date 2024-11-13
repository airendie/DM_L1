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
    set<BinaryMultiset *> m_subsets;

    // !TODO Сделать обновление (добавление/удаление) списка детей и кластерное удаление!!!!!!!!!!!!!

    // Количество элементов в бинарном множестве
    u8 m_bit_depth;

    /// Количество различных элементов в мультимножестве
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
    BinaryMultiset(u8 bit_depth = 0, u64 max_occurrence_multiplicity = DEFAULT_MAX_OCCURRENCE_MULTIPLICITY);
    /// @brief Конструктор мультимножества как подмножества универсума
    /// @param universum Родительский универсум. От него наследуются все параметры.
    BinaryMultiset(BinaryMultiset *universum);
    /// @brief Конструктор мультимножества как как копии мультимножества (без его наследников)
    /// @param other Копируемое мультимножество.
    BinaryMultiset(const BinaryMultiset &other);

    BinaryMultiset(BinaryMultiset &&other);


    /// @brief Перегрузка оператора присваивания. Копирует все, кроме наследников.
    /// @param other Копируемое мультимножество.
    /// @return Ссылка на объект изменяемый объект класса
    BinaryMultiset &operator=(const BinaryMultiset &other);
    BinaryMultiset &operator=(BinaryMultiset &&other) noexcept;


    /// @brief Оператор сравнения "не равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств одинаков, false - если различны
    bool operator==(const BinaryMultiset &other) const;

    /// @brief Оператор сравнения "не равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств различны, false - если одинаковы
    bool operator!=(const BinaryMultiset &other) const;

    /// @brief Выводит содержимое универсума на экран
    void print() const;

    /// @brief Возвращает количество элементов в мультимножетсве
    /// @return Размер вектора мультимножетсва
    u64 size() const;

    /// @brief Возращает разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    u8 bit_depth() const;

    /// @brief Возращает максимальную кратность вхождения элементов мультимножетсва
    /// @return Второй части пары <множество; число>
    u64 max_occurrence_multiplicity() const;

    /// @brief Возращает разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    vector<pair<BinarySet *, u64>> &data();

    /// @brief Возвращает i-ую пару из указателя на бинарный массив и его кратности в мультимножестве
    /// @param index Индекс запрашиваемой пары (index < size)
    /// @return i-ая пара из указателя на бинарный массив и его кратности в мультимножестве
    pair<BinarySet *, u64> operator[](u8 index) const;

    /// @brief Возвращает адрес i-ой пары из указателя на бинарный массив и его кратности в мультимножестве
    /// @param index Индекс запрашиваемой пары (index < size)
    /// @return Адрес i-ой пары в мультимножестве
    pair<BinarySet *, u64>& operator[](u8 index);



    /// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);
    void generateSeriesOfIncreasingNumbers();

    /// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
    void generateGrayCode();
    //void zeroes() { m_data};

    void clear();

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

