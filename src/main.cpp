#include <iostream>
#include <string>
#include <time.h>

#include "binary_multiset.hpp"

const u8 MAX_N = 16;



int main()
{
    srand(time(nullptr));

    std::string n;
    do
    {
        std::cout << "Please, input n (integer from 0 to " << std::to_string(MAX_N) << "): ";
        std::cin >> n;
    } while (!is_number(n));

    int bit_depth = std::stoi(n);
    std::cout << bit_depth << std::endl;
    BinaryMultiset u = BinaryMultiset(bit_depth);
    u.generateGrayCode();
    u.print();

    BinaryMultiset A(&u), B(&u);
    A.AutoInput();
    B.AutoInput();
    A.print();
    B.print();
    //BinaryMultiset k(u);
    //k.print();

    return 1;
}