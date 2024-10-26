#include <iostream>
#include "universum.hpp"

int main()
{
    int n;
    std::cout << "Please, input n: ";
    std::cin >> n;

    Universum u(n);
    u.print();

    return 1;
}