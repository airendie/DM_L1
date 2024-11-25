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

    /// @brief Метод, возвращающий разрядность элементов мультимножетсва
    /// @return Размер бинарного множества
    u8 bit_depth() const;

    /// @brief Функция замены значения кратности у переданного на вход множества
    /// @param Бинарное множество, кратность которого заменяется
    /// @param Новое значение кратности введенного множества
    /// @return true - если элемент заменен, false - если элемента нет в мультимнжоестве
    bool replace(const BinarySet &, u64 );
    /// @brief Функция замены значения кратности у переданного на вход множества
    /// @param Пара из бинарное множества, кратность которого заменяется, и нового значения его кратности
    /// @return true - если элемент заменен, false - если элемента нет в мультимнжоестве
    bool replace(const std::pair<BinarySet, u64> &);
    /// @brief Функция вставки или переписки элементов бинарного множества и его кратности
    /// @param Вставляемое множество
    /// @param Кратность вставляемого мультимножества
    void push_back_or_replace(const BinarySet &, u64 );
    /// @brief Функция вставки или переписки элементов бинарного множества и его кратности
    /// @param Пара из вставляемого множества и его кратности
    void push_back_or_replace(const std::pair<BinarySet, u64> &);

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

    /// @brief Функция генерации дополнения к мультимножеству
    /// @return Мультимножество, содержащее все элементы универсума мультимножества, кроме тех, что уже содержатся в мультимножестве
    BinaryMultiset operator!() const;

    /// @brief Функция генерации объединения двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из всех элементов операндов
    BinaryMultiset getUnion(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getUnion(BinaryMultiset &&) const;

    /// @brief Функция генерация пересечения двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из всех общих элементов операндов
    BinaryMultiset getIntersection(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getIntersection(BinaryMultiset &&) const;

    /// @brief Функция генерации разности двух мультимножеств
    /// @param Второй операнд-мультимножесво
    /// @return Мультимножество, состоящее из всех элементов первого операнда и не содержащее элементов второго
    BinaryMultiset getDifference(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getDifference(BinaryMultiset &&) const;

    /// @brief Функция генерации симметрической разности двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из всех элементов обоих операндов за исключением общих для обоих мультимножеств
    BinaryMultiset getSymmetricDifference(const BinaryMultiset &) const;

    // /// @brief
    // /// @param
    // /// @return
    // BinaryMultiset getSymmetricDifference(BinaryMultiset &&) const;

    /// @brief Функция генерации арифметической суммы двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из объединения операндов, кратность общих членов которых сложена
    BinaryMultiset operator+(const BinaryMultiset &) const;

    /// @brief Функция генерации арифметической разности двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из пересечения операндов, кратность общих членов которых равна разности соответственной кратностей их элементов в операндах-мультимножествах
    BinaryMultiset operator-(const BinaryMultiset &) const;

    /// @brief Функция генерации арифметическойго произведения двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из пересечения операндов, кратность общих членов которых равна произведению кратностей соответствующих элементов в мультимножествах
    BinaryMultiset operator*(const BinaryMultiset &) const;

    /// @brief Функция генерации арифметическойго частного двух мультимножеств
    /// @param Второй операнд-мультимножество
    /// @return Мультимножество, состоящее из пересечения операндов, кратность общих членов которых равна частному кратностей соответствующих элементов в мультимножествах
    BinaryMultiset operator/(const BinaryMultiset &) const;

    /// @brief Генерирует универсум как набор числел по возрастанию, начиная с 0 BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth);
    void generateSeriesOfIncreasingNumbers();
    /// @brief Генерирует универсум как код Грея BinaryMultiset generateGrayCodeUniversum(u8 bit_depth);
    void generateGrayCode();

    void clear();

    ~BinaryMultiset() { clear(); };
};

#endif // end of binary_set.hpp

