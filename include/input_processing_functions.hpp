#ifndef INPUT_PROCESSING_HPP
#define INPUT_PROCESSING_HPP

#include "def.hpp"
#include <string>

bool is_digits(const std::string &str);
bool is_binary(const std::string &str);

/// @brief Функция нахождения количества цифр целого числа
/// @param n
/// @return Количество цифр в целом числе n
template <typename t> t length(t n)
{
    t length = 0;

    for (; n != 0; ++length, n /= 10);
    return length;
}

u64 convertStrBinarySetToU64(const std::string &str);

bool is_number(std::string &str, u64 min_num, u64 max_num);
bool is_bit_depth(std::string &str );
bool is_occurrence_multiplicity(std::string &str, u64 max_occurrence_multiplicity);
bool is_binary_set(std::string &str, u8 bit_depth);

std::string inputBitDepth();

#endif // end of input_processing_functions.hpp

