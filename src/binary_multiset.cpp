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
    if (m_universum != nullptr)
    {
        m_data.clear();
        m_size = 0;

        bool is_finish = false;
        if (m_universum->m_bit_depth)
        {
            while (m_size < m_universum->m_size && !is_finish)
            {
                std::string str_bit_set;
                std::string str_occurrence_multiplicity;
                BinarySet new_set;
                u64 new_occurrence_multiplicity;
                u64 new_bit_depth;

                do
                {
                    std::cout << "Please, input binary set or 'f' to finish input. (Max length of set is " << std::to_string(m_bit_depth) << "," << std::endl
                              << "Format: \"011010\"): ";
                    std::cin >> str_bit_set;
                    if (str_bit_set == "f")
                    {
                        is_finish = true;
                        break;
                    }
                } while (!is_binary_set(str_bit_set, m_bit_depth));

                if (!is_finish)
                {
                    new_bit_depth = convertStrBinarySetToU64(str_bit_set);
                    new_set = BinarySet(new_bit_depth, m_bit_depth);

                    do
                    {
                        std::cout << "Please, print how many copies of these set will be in multiset (from 0 to " << std::to_string(m_max_occurrence_multiplicity) << ") \n or 'f' to finish (last one won't be saved): ";
                        std::cin >> str_occurrence_multiplicity;
                        if (str_occurrence_multiplicity == "f")
                        {
                            is_finish = true;
                            break;
                        }
                    } while (!is_occurrence_multiplicity(str_occurrence_multiplicity, m_max_occurrence_multiplicity));

                    if (!is_finish)
                    {
                        new_occurrence_multiplicity = std::stoi(str_occurrence_multiplicity);
                    }
                }
                if (!is_finish && new_occurrence_multiplicity)
                {
                    bool is_repeated = false;
                    for (int i = 0; i < m_size; ++i)
                    {
                        if (m_data[i].first == new_set)
                        {
                            m_data[i] = std::pair<BinarySet, u64>(new_set, new_occurrence_multiplicity);
                            is_repeated = true;
                            std::cout << "Binary set repeated. Overwriting." << std::endl;
                            break;
                        }
                    }
                    if (!is_repeated)
                    {
                        m_data.push_back(std::pair<BinarySet, u64>(BinarySet(new_bit_depth, m_bit_depth),
                                                                   std::stoi(str_occurrence_multiplicity)));
                        ++m_size;
                    }
                }

                if (is_finish)
                {
                    std::cout << "Input finished." << std::endl;
                    break;
                }
            }
        }
    }
    else
    {
        std::cout << "Input denied. Universum could not be empty." << std::endl;
    }
}

void BinaryMultiset::AutoInput()
{
    if (m_universum != nullptr)
    {
        if (m_universum->m_bit_depth)
        {
            m_data.clear();
            m_size = 0;
            for (int i = rand() % m_universum->m_size; i < m_universum->m_size; i += (rand() % m_universum->m_size + 1))
            {
                u64 occurrence = rand() % m_max_occurrence_multiplicity;
                if (occurrence != 0)
                {
                    m_data.push_back(std::pair<BinarySet, u64>(m_universum->m_data[i].first, occurrence));
                    ++m_size;
                }
            }
        }
    }
    else
        std::cout << "Universum for this multiset is not declarated." << std::endl;
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

    if (m_bit_depth && m_size)
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

BinaryMultiset BinaryMultiset::operator!() const
{
    if (m_universum != nullptr)
    {
        BinaryMultiset result;

        for (int j = 0; j < m_universum->m_size; ++j)
        {
            bool is_found = false;
            for (int i = 0; i < m_size; ++i)
            {
                if (m_universum->m_data[j].first == m_data[i].first)
                {
                    is_found = true;

                    if (m_data[i].second != m_universum->max_occurrence_multiplicity())
                    {
                        result.m_data.push_back(std::pair<BinarySet, u64>(m_universum->data()[j].first, m_universum->max_occurrence_multiplicity() - m_data[i].second));
                        ++result.m_size;

                        std::cout << "Added: " << result.m_data[result.m_size - 1].first << ", " << std::to_string(m_universum->max_occurrence_multiplicity() - m_data[i].second) << std::endl;
                    }
                    break;
                }
            }
            if (!is_found)
            {
                result.m_data.push_back(m_universum->data()[j]);
                ++result.m_size;

                std::cout << "Added: " << result.m_data[result.m_size - 1].first << ", " << std::to_string(result.m_data[result.m_size - 1].second) << std::endl;
            }
        }
        return result;
    }
    return *this;
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
