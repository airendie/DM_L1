#include <binary_multiset.hpp>
#include <iostream>
#include <stdexcept>

using std::cout;

BinaryMultiset::BinaryMultiset(u8 bit_depth,
                               u32 max_occurrence_multiplicity) : m_universum(nullptr),
                                                                  m_bit_depth(bit_depth),
                                                                  m_size((u_int64_t)1 << m_bit_depth),
                                                                  m_max_occurrence_multiplicity(max_occurrence_multiplicity)
{
}

BinaryMultiset::BinaryMultiset(BinaryMultiset *universum) : m_universum(universum),
                                                            m_bit_depth((m_universum) ? m_universum->m_bit_depth : 0),
                                                            m_size((m_universum) ? m_universum->m_size : 0),
                                                            m_max_occurrence_multiplicity((m_universum) ? m_universum->m_max_occurrence_multiplicity : 0)
{
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

u32 max_occurrence_multiplicity() const
{
    return m_max_occurence_multiplicity;
}

pair<BinarySet, u64> BinaryMultiset::operator[](u8 index) const
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
    return pair<BinarySet, u64>{BinarySet(), 0};
}

BinaryMultiset generateGrayCode(u8 bit_depth)
{
    BinaryMultiset new_set(bit_depth);
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
            // std::cout << "j: " << j << '\n' << i << " is " <<
            //                 ((m_gray_code[i][j]) ? "behind " : "not behind ") <<
            //                 max_limit_of_current_interval <<
            //                   " and " << center_of_current_interval << '\n';
        }
    }
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

BinaryMultiset generateSeriesOfIncreasingNumbers(u8 bit_depth)
{
    BinaryMultiset new_set(bit_depth);

    for (int i = 0; i < new_set.size(); ++i)
    {
        new_set[i].first.setNumber(i);
    }
}
