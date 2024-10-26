#include <iostream>
#include "universum.hpp"

int main()
{
    u64 n;
    std::cout << "Please, input n: ";
    std::cin >> n;

    //Universum u(n);
    //u.print();
    //u.generateIncrNumSeq();
    //u.print();
    BinaryNumber bn(n, 3);
    bn.setNumber(n);
    bn.print();
    std::cout << std::endl << bn.toUInt64()<< std::endl;


    return 1;
}