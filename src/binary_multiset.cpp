#include <binary_multiset.hpp>
#include <iostream>
#include <stdexcept>

using std::cout;

BinaryMultiset::BinaryMultiset(u8 bit_depth,
                               u64 max_occurrence_multiplicity) : m_universum(nullptr),
                                                                  m_bit_depth(bit_depth),
                                                                  m_size((u_int64_t)1 << m_bit_depth),
                                                                  m_max_occurrence_multiplicity(max_occurrence_multiplicity)
{
    //m_data.resize(m_size, std::pair<BinarySet *, u64>(nullptr, m_max_occurrence_multiplicity));
    addToUniversumSubsets();
}

BinaryMultiset::BinaryMultiset(BinaryMultiset *universum) : m_universum(universum),
                                                            m_bit_depth((m_universum) ? m_universum->m_bit_depth : 0),
                                                            m_size((m_universum) ? m_universum->m_size : 0),
                                                            m_max_occurrence_multiplicity((m_universum) ? m_universum->m_max_occurrence_multiplicity : 0)
{
    //m_data.resize(m_size, std::pair<BinarySet *, u64>(nullptr, m_max_occurrence_multiplicity));

    addToUniversumSubsets();
}

// Наследования производных мультимножеств не происходит. Только копирование данных.
BinaryMultiset::BinaryMultiset(const BinaryMultiset &other) : m_universum(other.m_universum),
                                                              m_data(other.m_data),
                                                              m_bit_depth(other.m_bit_depth),
                                                              m_size(other.m_bit_depth),
                                                              m_max_occurrence_multiplicity(other.m_max_occurrence_multiplicity)
{
    addToUniversumSubsets();
}

BinaryMultiset::BinaryMultiset(BinaryMultiset &&other)
{
    clear();

    *this = std::move(other);
    other = nullptr;
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
    // for (u64 i = 0; i < m_size; ++i)
    // {
    //     m_data[i] = std::pair<BinarySet *, u64>(new BinarySet(i, m_bit_depth), m_max_occurrence_multiplicity);
    //     std::cout << "Added: " << BinarySet(i, m_bit_depth) << " in " << i << std::endl;
    // }
}

void BinaryMultiset::generateGrayCode()
{
    // clearSubsets();
    // if (m_universum == nullptr)
    //     clearData();
    //  for (u64 i = 0; i < m_size; ++i)
    //  {
    //      for (u8 j = 0; j < m_bit_depth; ++j)
    //      {
    //          int full_interval = 1 << (j + 2);
    //          int half_of_interval = 1 << (j + 1);
    //          int max_limit_of_current_interval = full_interval * (1 + i / full_interval) - (1 << j);

    //         int center_of_current_interval = max_limit_of_current_interval - half_of_interval;
    //         m_data[i].first[j] = (i >= center_of_current_interval && i < max_limit_of_current_interval);
    //         m_data[i].second = m_max_occurrence_multiplicity;
    //         // std::cout << "j: " << j << '\n' << i << " is " <<
    //         //                 ((m_gray_code[i][j]) ? "behind " : "not behind ") <<
    //         //                 max_limit_of_current_interval <<
    //         //                   " and " << center_of_current_interval << '\n';
    //     }
    //     std::cout << "Added: " << *m_data[i].first << " in " << i << std::endl;
    // }
}

void BinaryMultiset::clear()
{
    // Кластерное удаление всех "детей"
    for (auto i : m_subsets)
    {
        delete i;
    }
    m_subsets.clear();

    // Очистка данных, если "выше" никого нет
    if (m_universum == nullptr)
    {
        for (auto i : m_data)
        {
            delete i.first;
            i.first = nullptr;
        }

        m_data.clear();
    }
    m_bit_depth = 0;
    m_size = 0;
    m_max_occurrence_multiplicity = 0;

    // Удаление из списка детей родительского универсума
    removefromUniversumSubsets();
    m_universum = nullptr;
}


bool BinaryMultiset::operator==(const BinaryMultiset &other) const
{
    return (m_universum == other.m_universum &&
            m_bit_depth == other.m_bit_depth &&
            m_max_occurrence_multiplicity == other.m_bit_depth &&
            m_data == other.m_data &&
            m_subsets == other.m_subsets);
}

bool BinaryMultiset::operator!=(const BinaryMultiset &other) const
{
    return (m_universum != other.m_universum ||
            m_bit_depth != other.m_bit_depth ||
            m_max_occurrence_multiplicity != other.m_bit_depth ||
            m_data != other.m_data ||
            m_subsets != other.m_subsets);
}

void BinaryMultiset::print() const
{
    cout << "BinaryMultiset: \n";

    if (m_bit_depth)
    {
        for (int i = 0; i < m_size; ++i)
        {
            cout << i << ":  { " << *m_data[i].first << ", " << m_data[i].second << " }\n";
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

vector<pair<BinarySet *, u64>> &BinaryMultiset::data()
{
    return m_data;
}

pair<BinarySet *, u64> BinaryMultiset::operator[](u8 index) const
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
    return pair<BinarySet *, u64>{nullptr, 0};
}

pair<BinarySet *, u64> &BinaryMultiset::operator[](u8 index)
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

void BinaryMultiset::addToUniversumSubsets()
{
    if (m_universum != nullptr)
    {
        std::pair<std::set<BinaryMultiset *>::iterator, bool> i = m_universum->m_subsets.insert(this);
        if (!i.second)
        {
            std::cout << "Insertion failure!\n";
        }
    }
}

void BinaryMultiset::removefromUniversumSubsets()
{
    if (m_universum != nullptr)
    {
        set<BinaryMultiset *>::iterator i;
        if ((i = m_universum->m_subsets.find(this)) != m_universum->m_subsets.end())
        {
            m_universum->m_subsets.erase(i);
        }
        else
        {
            cout << "Binary Subset is not found!\n";
        }
    }
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
            // std::cout << "j: " << j << '\n' << i << " is " <<
            //                 ((m_gray_code[i][j]) ? "behind " : "not behind ") <<
            //                 max_limit_of_current_interval <<
            //                   " and " << center_of_current_interval << '\n';
        }
    }
    return new_set;
}

// BinarySet &BinaryMultiset::operator[](u8 index)
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

BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth, u64 max_occurance_multiplicity)
{
    BinaryMultiset new_set(bit_depth, max_occurance_multiplicity);

    for (u64 i = 0; i < new_set.size(); ++i)
    {
        new_set.data()[i] = (std::pair<BinarySet *, u64>(new BinarySet(i, bit_depth), max_occurance_multiplicity));
        std::cout << "Added: " << i << " in " << i << std::endl;
    }
    return new_set;
}
