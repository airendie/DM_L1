#include <iostream>
#include <string>
#include "universum.hpp"

const u8 MAX_N = 16;

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool is_correct(const std::string &str)
{
    // Проверка на наличие элементов в строке
    if (!str.empty())
    {
        // Проверка на наличие только цифр в строке
        if (is_digits(str))
        {
            // Проверка первого элемента на 0 (Явный запрет формата: "n = 0123")
            if (str[0] != '0' || str.length() == 1)
            {
                // Длина введенного числа может быть больше,
                // чем длина типа int, что уронит программу
                // Только если длина введенного числа не больше длины MAX_N,
                // имеет смысл сравнить числовые значения

                // Проверка числа-строки на возможность быть представленным
                // в int'е и, если такая возможность есть, проверка на не
                // превышение максимального значения разрядности
                if (std::to_string(MAX_N).length() >= str.length() &&
                    MAX_N >= std::stoi(str))
                {
                    return true;
                }
                std::cout << "Incorrect input! Bit depth could not be more than " << std::to_string(MAX_N) << "...\n";
            }
            else
            {
                std::cout << "Incorrect input! Number could not start from zero...\n";
            }
        }
        else
        {
            std::cout << "Incorrect input! Only numbers, please...\n";
        }
    }
    else
    {
        std::cout << "Incorrect input! Number could not be empty...\n";
    }
    return false;
}

int main()
{
    std::string n;
    std::cout << "Please, input n (integer from 0 to "<< (int)MAX_N << "): ";
    std::cin >> n;

    if (is_correct(n))
    {
        // std::cout << "Correct.\n";

        Universum u(std::stoi(n));
        //u.print();
        u.generateGrayCode();
        u.print();
        // //  BinaryNumber bn(n, 3);
        // //  bn.setNumber(n);
        // //  bn.print();
        //  std::cout << std::endl << bn.toUInt64()<< std::endl;
    }

    return 1;
}