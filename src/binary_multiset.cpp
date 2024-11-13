#include "binary_multiset.hpp"
#include "input_processing_functions.hpp"
#include <iostream>
#include <stdexcept>

using std::cout;

BinaryMultiset::BinaryMultiset(u8 bit_depth,
                               u64 max_occurrence_multiplicity) : m_universum(nullptr),
                                                                  m_bit_depth(bit_depth),
                                                                  m_size((u_int64_t)1 << m_bit_depth),
                                                                  m_max_occurrence_multiplicity(max_occurrence_multiplicity)
{
    m_data.resize(m_size);
}

BinaryMultiset::BinaryMultiset(BinaryMultiset *universum) : m_universum(universum),
                                                            m_bit_depth((m_universum) ? m_universum->m_bit_depth : 0),
                                                            m_max_occurrence_multiplicity((m_universum) ? m_universum->m_max_occurrence_multiplicity : 0)
{
}

// Наследования производных мультимножеств не происходит. Только копирование данных.
BinaryMultiset::BinaryMultiset(const BinaryMultiset &other) : m_universum(other.m_universum),
                                                              m_data(other.m_data),
                                                              m_bit_depth(other.m_bit_depth),
                                                              m_max_occurrence_multiplicity(other.m_max_occurrence_multiplicity)
{
}

BinaryMultiset::BinaryMultiset(BinaryMultiset &&other)
{
    clear();

    *this = std::move(other);
    other = nullptr;
}

void BinaryMultiset::ManualInput()
{
    std::cout << "Please, input binary set or 'f' to finish input. (Format: \"011010\"): ";
    std::string s;
    std::cin >> s;
    if (is_binary(s))
    {
        if (s.length() <= m_bit_depth)
        {
            std::cout << "Correct." << std::endl;
        }
        else
        {
        }
    }
    else
    {
        std::cout << "Incorrect input. Only '0' and '1' please... " << std::endl;
    }

    std::cout << "Please, print how many copies of these set will be in multiset (from 0 to " << m_max_occurrence_multiplicity << ") or 'f' to finish (last one won't be saved): ";
    std::cin >> s;
}

void BinaryMultiset::AutoInput()
{
    if (m_universum != nullptr)
    {
        m_data.clear();
        m_size = 0;
        for (int i = rand() % m_universum->m_size; i < m_universum->m_size; i += (rand() % m_universum->m_size + 1))
        {
            m_data.push_back(std::pair<BinarySet, u64>(m_universum->m_data[i].first, rand() % m_max_occurrence_multiplicity));
            ++m_size;
        }
    }
    else
        std::cout << "Universum to this multiset is not declarated." << std::endl;
}

BinaryMultiset &BinaryMultiset::operator=(const BinaryMultiset &other)
{
    if (*this != other)
    {
        clear();

        m_universum = other.m_universum;
        m_bit_depth = other.m_bit_depth;
        m_size = other.m_size;
        m_max_occurrence_multiplicity = other.m_max_occurrence_multiplicity;
        m_data = other.m_data;
        // При создании мультимножества множество наследников не переносится
        // m_subsets = other.m_subsets;
    }

    return *this;
}

BinaryMultiset &BinaryMultiset::operator=(BinaryMultiset &&other) noexcept
{
    clear();

    *this = std::move(other);
    other = nullptr;

    return *this;
}

void BinaryMultiset::generateSeriesOfIncreasingNumbers()
{
    for (u64 i = 0; i < m_size; ++i)
    {
        m_data[i] = std::pair<BinarySet, u64>(BinarySet(i, m_bit_depth), m_max_occurrence_multiplicity);
        std::cout << "Added: " << BinarySet(i, m_bit_depth) << " in " << i << std::endl;
    }
}

void BinaryMultiset::generateGrayCode()
{
    for (u64 i = 0; i < m_size; ++i)
    {
        m_data[i].first.resize(m_bit_depth);
        for (u8 j = 0; j < m_bit_depth; ++j)
        {
            int full_interval = 1 << (j + 2);
            int half_of_interval = 1 << (j + 1);
            int max_limit_of_current_interval = full_interval * (1 + i / full_interval) - (1 << j);

            int center_of_current_interval = max_limit_of_current_interval - half_of_interval;
            m_data[i].first[j] = (i >= center_of_current_interval && i < max_limit_of_current_interval);
            m_data[i].second = m_max_occurrence_multiplicity;

            // std::cout << m_data[i].first[j];
            // std::cout << "j: " << j << '\n' << i << " is " <<
            //                 ((m_gray_code[i][j]) ? "behind " : "not behind ") <<
            //                 max_limit_of_current_interval <<
            //                   " and " << center_of_current_interval << '\n';
        }
        // std::cout << " Added: " << m_data[i].first << " in " << i << std::endl;
    }
}

void BinaryMultiset::clear()
{
    // Очистка данных
    m_data.clear();
    m_bit_depth = 0;
    m_size = 0;
    m_max_occurrence_multiplicity = 0;
    m_universum = nullptr;
}

bool BinaryMultiset::operator==(const BinaryMultiset &other) const
{
    return (m_universum == other.m_universum &&
            m_bit_depth == other.m_bit_depth &&
            m_max_occurrence_multiplicity == other.m_bit_depth &&
            m_data == other.m_data);
}

bool BinaryMultiset::operator!=(const BinaryMultiset &other) const
{
    return (m_universum != other.m_universum ||
            m_bit_depth != other.m_bit_depth ||
            m_max_occurrence_multiplicity != other.m_bit_depth ||
            m_data != other.m_data);
}

void BinaryMultiset::print() const
{
    cout << "BinaryMultiset: \n";

    if (m_bit_depth)
    {
        for (int i = 0; i < m_size; ++i)
        {
            cout << i << ":  { " << m_data[i].first << ", " << m_data[i].second << " }\n";
        }
    }
    else
    {
        cout << "0: ∅\n";
    }
}

u64 BinaryMultiset::size() const
{
    return m_size;
}

u8 BinaryMultiset::bit_depth() const
{
    return m_bit_depth;
}

u64 BinaryMultiset::max_occurrence_multiplicity() const
{
    return m_max_occurrence_multiplicity;
}

vector<pair<BinarySet, u64>> &BinaryMultiset::data()
{
    return m_data;
}

pair<BinarySet, u64> BinaryMultiset::operator[](u64 index) const
{
    try
    {
        if (index >= m_size)
            throw std::out_of_range("Out of range! Index is greater than size.");

        return m_data[index];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return pair<BinarySet, u64>{};
}

pair<BinarySet, u64> &BinaryMultiset::operator[](u64 index)
{
    try
    {
        if (index >= m_size)
            throw std::out_of_range("Out of range! Index is greater than size.");

        return m_data[index];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return *m_data.end();
}

BinaryMultiset generateGrayCode(u8 bit_depth, u64 max_occurrence_multiplicity)
{
    BinaryMultiset new_set(bit_depth, max_occurrence_multiplicity);
    // По массивам
    for (size_t i = 0; i < new_set.size(); ++i)
    {
        for (size_t j = 0; j < new_set.bit_depth(); ++j)
        {
            int full_interval = 1 << (j + 2);
            int half_of_interval = 1 << (j + 1);
            int max_limit_of_current_interval = full_interval * (1 + i / full_interval) - (1 << j);

            int center_of_current_interval = max_limit_of_current_interval - half_of_interval;
            new_set[i].first[j] = (i >= center_of_current_interval &&
                                   i < max_limit_of_current_interval);
            new_set[i].second = max_occurrence_multiplicity;
        }
    }
    return new_set;
}

BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth, u64 max_occurance_multiplicity)
{
    BinaryMultiset new_set(bit_depth, max_occurance_multiplicity);

    for (u64 i = 0; i < new_set.size(); ++i)
    {
        new_set.data()[i] = (std::pair<BinarySet, u64>(BinarySet(i, bit_depth), max_occurance_multiplicity));
        std::cout << "Added: " << i << " in " << i << std::endl;
    }
    return new_set;
}
