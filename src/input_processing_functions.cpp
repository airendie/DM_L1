#include "input_processing_functions.hpp"
#include <iostream>
#include <string>

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool is_binary(const std::string &str)
{
    return str.find_first_not_of("01") == std::string::npos;
}

u64 convertStrBinarySetToU64(const std::string &str)
{
    int64_t result = 0;

    size_t strLength = str.length();
    for (int i = 0; i < strLength; ++i)
    {
        // int64_t n1 = str[i];
        // u_int64_t n2 = str[i];
        // std::cout << i << ": " << str[i] << " " << (u64)str[i] - 48 << std::endl;
        result += ((((u64)str[i] - 48)) << (strLength - i - 1));
    }
    // std::cout << "Длина: " << strLength << std::endl
    //           << "Строка: " << str << std::endl
    //           << "Число: " << std::to_string(result) << std::endl;
    return result;
}

bool is_bit_depth(std::string &str)
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
                // std::cout << signif << std::endl;
                if (length(MAX_N) >= signif.length() && MAX_N >= std::stoi(signif))
                {
                    // std::cout << "Correct." << std::endl;
                    return true;
                }
                else
                {
                    std::cout << "Incorrect input! Bit depth could not be more than " << std::to_string(MAX_N) << "...\n";
                }
            }
            // Введенное число - 0
            else
            {
                // std::cout << "Correct." << std::endl;
                return true;
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

bool is_occurrence_multiplicity(std::string &str, u64 max_occur)
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
                std::string significant_part = str.substr(first_significant_digit);
                // std::cout << signif << std::endl;
                std::cout << "signif: " <<  significant_part << std::endl;
                // Проверка на превышение максимальной длины ввода
                if (significant_part.length() <= length(max_occur) && max_occur >= std::stoi(significant_part))
                {
                    return true;
                    // std::cout << "Correct." << std::endl;
                }
                else
                {
                    // std::cout << "max_o_m: " << (int)max_occur << ", " << length(max_occur) << std::endl
                    //           << "o_m: " << signif << ", " << signif.length() << std::endl;
                    std::cout << "Incorrect input! Occurrence multiplicity could not be more than " << std::to_string(max_occur) << "...\n";
                }
            }
            // Введенное число - 0
            else
            {
                //    std::cout << "Incorrect input! Number could not start from zero...\n";
                // std::cout << "Correct." << std::endl;
                return true;
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

bool is_binary_set(std::string &str, u8 bit_depth)
{
    // Проверка на отсутствие элементов в строке
    if (!str.empty())
    {
        // Проверка на наличие чего-то, кроме нулей и единиц
        if (is_binary(str))
        {
            // Проверка на превышение максимальной длины
            if (str.length() <= bit_depth)
            {
                std::cout << "Correct." << std::endl;
                return true;
            }
            else
            {
                std::cout << "Incorrect input! Length of the binary set could not be more than " << std::to_string(bit_depth) << "...\n";
            }
        }
        else
        {
            std::cout << "Incorrect input! Only zeroes and ones, please...\n";
        }
    }
    else
    {
        std::cout << "Incorrect input! Binary set could not be empty...\n";
    }

    return false;
}
