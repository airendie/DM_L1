#ifndef UNIVERSUM_HPP
#define UNIVERSUM_HPP

#include "binary_number.hpp"

using std::vector;

class Universum
{
    // max 31
    const u8 m_bit_depth;
    // Universum size = 2^n. Max: 2^32 - 1
    u_int64_t m_size;
    // Vector of generated Gray's code for all arrays in Universum
    vector<BinaryNumber> m_gray_code;

public:
    Universum(u_int8_t n = 0);

    void print();
};

#endif // end of unversum.hpp

