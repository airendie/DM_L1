#include <iostream>
#include <string>

#include "binary_multiset.hpp"

const u8 MAX_N = 16;

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

u8 length(u8 n)
{
    u8 length = 0;

    for(; n != 0; ++length, n /= 10 );

    std::cout << (int)length <<std::endl;
    return length;
}

int to_number(std::string &str)
{
    // Проверка на наличие элементов в строке
    if (!str.empty())
    {
        // Проверка на наличие только цифр в строке
        if (is_digits(str))
        {
            // Поиск первой ненулевой цифры
            size_t first_significant_digit = str.find_first_not_of("0");
            // Если в числе есть хотя бы одна ненулевая цифра
            if (first_significant_digit != std::string::npos)
            {
                // Длина введенного числа может быть больше,
                // чем длина типа int, что уронит программу
                // Только если длина введенного числа не больше длины MAX_N,
                // имеет смысл сравнить числовые значения

                // Проверка значимой части числа-строки на возможность
                // быть преобразованной в int и, если такая возможность есть,
                // проверка на не
                // превышение максимального значения разрядности

                std::string signif = str.substr(first_significant_digit);
                std::cout << signif << std::endl;
                if (length(MAX_N) >= signif.length() && MAX_N >= std::stoi(signif))
                {
                    std::cout << "Correct." << std::endl;
                    return std::stoi(str.substr(first_significant_digit));
                }
                else
                {
                    std::cout << "Incorrect input! Bit depth could not be more than " << std::to_string(MAX_N) << "...\n";
                }
            }
            // Введенное число - 0
            else
            {
            //    std::cout << "Incorrect input! Number could not start from zero...\n";

                std::cout << "Correct." << std::endl;
                return 0;
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

    return -1;
}

int main()
{
    std::string n;
    std::cout << "Please, input n (integer from 0 to " << std::to_string(MAX_N) << "): ";
    std::cin >> n;

    BinaryMultiset u(to_number(n));
    // u.generateSeriesOfIncreasingNumbers();
    //BinaryMultiset k(u);
    u.print();
    //k.print();

    return 1;
}