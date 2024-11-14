#include <iostream>
#include <string>
#include <time.h>


#include "input_processing_functions.hpp"
#include "binary_multiset.hpp"


static void ui()
{
    srand(time(nullptr));

    // n input and check
    std::string n;
    do
    {
        std::cout << "Please, input n (integer from 0 to " << std::to_string(MAX_N) << "): ";
        std::cin >> n;
    } while (!is_bit_depth(n));

    int bit_depth = std::stoi(n);
    std::cout << bit_depth << std::endl;

    BinaryMultiset u = BinaryMultiset(bit_depth);

    BinaryMultiset A(&u), B(&u);
    u.generateGrayCode();
    u.print();

    A.AutoInput();
    B.ManualInput();

    std::cout << "A ";
    A.print();
    std::cout << "B ";
    B.print();
}

int main()
{
    ui();

    return 1;
}