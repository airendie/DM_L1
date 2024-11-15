#ifndef INPUT_PROCESSING
#define INPUT_PROCESSING

#include "def.hpp"
#include <string>

bool is_digits(const std::string &str);
bool is_binary(const std::string &str);

/// @brief Функция нахождения количества цифр числа типа u_int8_t
/// @param n
/// @return Количество цифр в числе n
template <typename t> t length(t n)
{
    t length = 0;

    for (; n != 0; ++length, n /= 10);
    return length;
}

u64 convertStrBinarySetToU64(const std::string &str);

bool is_bit_depth(std::string &str);
bool is_occurrence_multiplicity(std::string &str, u64 max_occurrence_multiplicity);
bool is_binary_set(std::string &str, u8 bit_depth);

#endif // end of input_processing_functions.hpp

