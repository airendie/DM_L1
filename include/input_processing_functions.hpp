#ifndef INPUT_PROCESSING
#define INPUT_PROCESSING

#include "def.hpp"
#include <string>

bool is_digits(const std::string &str);
bool is_binary(const std::string &str);

u8 length(u8 n);
u64 convertStrBinarySetToU64(const std::string &str);

bool is_bit_depth(std::string &str);
bool is_occurrence_multiplicity(std::string &str, u64 max_occurrence_multiplicity);
bool is_binary_set(std::string &str, u8 bit_depth);

#endif // end of input_processing_functions.hpp

