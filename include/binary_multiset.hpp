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

    // Количество элементов в бинарном множестве
    u8 m_bit_depth;

    /// Количество различных элементов в мультимножестве
    u64 m_size;

    // Максимальная кратность элементов в мультимножестве
    u64 m_max_occurrence_multiplicity;

    // Множество пар из указателей на множество в универсуме и
    // их количества в конкретном мультимножетсве
    vector<pair<BinarySet, u64>> m_data;

public:
    /// @brief Конструктор универсума
    /// @param bit_depth Количество элементов в бинарных массиах
    /// @param max_occurrence_multiplicity Максимальная разрядность в мультимножестве
    BinaryMultiset(u8 bit_depth = 0, u64 max_occurrence_multiplicity = 0);
    /// @brief Конструктор мультимножества как подмножества универсума
    /// @param universum Родительский универсум. От него наследуются все параметры.
    BinaryMultiset(BinaryMultiset *universum);
    /// @brief Конструктор мультимножества как как копии мультимножества (без его наследников)
    /// @param other Копируемое мультимножество.
    BinaryMultiset(const BinaryMultiset &other) = default;

    // BinaryMultiset(BinaryMultiset &&other) = default;

    void ManualInput();
    void AutoInput();

    /// @brief Перегрузка оператора присваивания.
    /// @param other Копируемое мультимножество.
    /// @return Ссылка на объект изменяемый объект класса
    BinaryMultiset &operator=(const BinaryMultiset &other);
    // BinaryMultiset &operator=(BinaryMultiset &&other) noexcept;

    /// @brief Оператор сравнения "равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств одинаков, false - если различны
    bool operator==(const BinaryMultiset &other) const;
    /// @brief Оператор сравнения "равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств одинаков, false - если различны
    bool operator==(BinaryMultiset &&other) const;
    /// @brief Оператор сравнения "не равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств различны, false - если одинаковы
    bool operator!=(const BinaryMultiset &other) const;
    /// @brief Оператор сравнения "не равно"
    /// @param other Мультимножество, с которым происходит сравнение
    /// @return true - если значения мультимножеств различны, false - если одинаковы
    bool operator!=(BinaryMultiset &&other) const;

    /// @brief Выводит содержимое универсума на экран
    void print() const;

    /// @brief Метод, возвращающий количество элементов в мультимножетсве
    /// @return Размер вектора мультимножетсва
    u64 size() const;

    /// @brief Метод, возвращаюзий разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    u8 bit_depth() const;

    bool replace(const BinarySet &, u64 );
    bool replace(const std::pair<BinarySet, u64> &);
    void push_back_or_replace(const BinarySet &, u64 );
    void push_back_or_replace(const std::pair<BinarySet, u64> &);

    void setBitDepth(u8 new_bit_depth);

    /// @brief Метод, возвращающий максимальную кратность вхождения элементов мультимножетсва
    /// @return Второй части пары <множество; число>
    u64 max_occurrence_multiplicity() const;

    /// @brief Метод, возвращающий ссылку на содержимое мультимножетсва
    /// @return Размер бинарного множества
    vector<pair<BinarySet, u64>> &data();
    /// @brief Метод, возвращающий копию содержимого мультимножетсва
    /// @return Размер бинарного множества
    vector<pair<BinarySet, u64>> data() const;

    /// @brief Метод, возвращающий адрес i-ой пары из указателя на бинарный массив и его кратности в мультимножестве
    /// @param index Индекс запрашиваемой пары (index < size)
    /// @return Адрес i-ой пары в мультимножестве
    pair<BinarySet, u64> &operator[](u64 index);
    /// @brief Метод, возвращающий i-ую пару из указателя на бинарный массив и его кратности в мультимножестве
    /// @param index Индекс запрашиваемой пары (index < size)
    /// @return i-ая пара из указателя на бинарный массив и его кратности в мультимножестве
    pair<BinarySet, u64> operator[](u64 index) const;


    // Multiset's operations

    /// @brief
    /// @param
    /// @return
    BinaryMultiset operator!() const;

    /// @brief
    /// @param
    /// @return
    BinaryMultiset getUnion(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getUnion(BinaryMultiset &&) const;

    /// @brief
    /// @param
    /// @return
    BinaryMultiset getIntersection(const BinaryMultiset &) const;


    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getIntersection(BinaryMultiset &&) const;

    /// @brief
    /// @param
    /// @return
    BinaryMultiset getDifference(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getDifference(BinaryMultiset &&) const;

    /// @brief
    /// @param
    /// @return
    BinaryMultiset getSymmetricalDifference(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getSymmetricalDifference(BinaryMultiset &&) const;

    /// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);
    void generateSeriesOfIncreasingNumbers();
    /// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
    void generateGrayCode();

    void clear();

    ~BinaryMultiset() { clear(); };
};

// /// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);
// BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth,
//                                                  u64 max_occurrence_multiplicity =
//                                                      DEFAULT_MAX_OCCURRENCE_MULTIPLICITY);

// /// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
// BinaryMultiset generateGrayCode(u8 bit_depth,
//                                 u64 max_occurrence_multiplicity =
//                                     DEFAULT_MAX_OCCURRENCE_MULTIPLICITY);

#endif // end of binary_set.hpp

