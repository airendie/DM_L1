#include <iostream>
#include <string>
#include <time.h>

#include "input_processing_functions.hpp"
#include "binary_multiset.hpp"

static void main_loop()
{
    srand(time(nullptr));

    // n input and check
    // std::string n;
    // do
    // {
    //     std::cout << "Please, input n (integer from 0 to " << std::to_string(MAX_N) << "): ";
    //     getline(std::cin, n);
    // } while (!is_bit_depth(n));

    // int bit_depth = std::stoi(n);
    // std::cout << bit_depth << std::endl;

    int bit_depth = 3;
    BinaryMultiset u = BinaryMultiset(3, 1000);

    BinaryMultiset A(&u), B(&u);
    u.generateGrayCode();
    std::cout << "Universum: " << std::endl;
    u.print();
    std::cout << std::endl;

    A.push_back_or_replace(BinarySet(2, bit_depth), 10);
    A.push_back_or_replace(BinarySet(3, bit_depth), 2);
    A.push_back_or_replace(BinarySet(1, bit_depth), 5);
    A.push_back_or_replace(BinarySet(0, bit_depth), 7);

    B.push_back_or_replace(BinarySet(2, bit_depth), 7);
    B.push_back_or_replace(BinarySet(3, bit_depth), 2);
    B.push_back_or_replace(BinarySet(0, bit_depth), 1000);

    //A.AutoInput();
    //A.AutoInput();
    //B.AutoInput();

    std::cout << "A:" << std::endl;
    A.print();
    std::cout << std::endl;

    std::cout << "B:" << std::endl;
    B.print();
    std::cout << std::endl;

    std::cout << "!A:" << std::endl;
    (!A).print();
    std::cout << std::endl;

    std::cout << "!B:" << std::endl;
    (!B).print();
    std::cout << std::endl;

    std::cout << "A union B:" << std::endl;
    A.getUnion(B).print();
    std::cout << std::endl;

    std::cout << "B union A:" << std::endl;
    B.getUnion(A).print();
    std::cout << std::endl;

    std::cout << "A intersection B:" << std::endl;
    A.getIntersection(B).print();
    std::cout << std::endl;

    std::cout << "B intersection A:" << std::endl;
    B.getIntersection(A).print();
    std::cout << std::endl;

    std::cout << "A \\ B:" << std::endl;
    (A.getDifference(B)).print();
    std::cout << std::endl;

    std::cout << "B \\ A:" << std::endl;
    (B.getDifference(A)).print();
    std::cout << std::endl;

    std::cout << "A symmetrical difference B:" << std::endl;
    A.getSymmetricalDifference(B).print();
    std::cout << std::endl;

    std::cout << "B symmetrical difference A:" << std::endl;
    B.getSymmetricalDifference(A).print();
    std::cout << std::endl;
}

int main()
{
    main_loop();

    return 1;
}