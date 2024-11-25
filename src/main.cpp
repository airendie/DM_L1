#include <iostream>
#include <string>
#include <time.h>

#include "input_processing_functions.hpp"
#include "binary_multiset.hpp"

void main_loop()
{
    std::string n = inputBitDepth();
    int bit_depth = std::stoi(n);

    BinaryMultiset u = BinaryMultiset(bit_depth, 10);

    u.generateGrayCode();
    std::cout << "Universum: " << std::endl;
    u.print();
    std::cout << std::endl;

    BinaryMultiset A(&u), B(&u);

    for (size_t i = 0; i < 2; ++i)
    {
        BinaryMultiset *activeSet = (!i) ? &A : &B;

        std::string s;
        std::cout << "Please, choose input mode for multiset " << ((!i) ? "A" : "B") << " (1 - manual input, 2 - random generated): ";
        getline(std::cin, s);

        bool is_end = false;
        do
        {
            // input check
            while (!is_number(s, 1, 2))
            {
                std::cout << "Please, try again: ";
                getline(std::cin, s);
            }

            switch (std::stoi(s))
            {
            case 1:
                activeSet->ManualInput();
                is_end = true;
                break;
            case 2:
                activeSet->AutoInput();
                is_end = true;
                break;
            default:
                break;
            }
        } while (!is_end);

        std::cout << ((!i) ? "A" : "B") << ":" << std::endl;
        activeSet->print();
        std::cout << std::endl;
    }

    bool is_end = false;
    bool is_restart = false;
    do
    {
        std::cout << " ______________________________________________ " << std::endl
                  << "|                    Menu:                     |" << std::endl
                  << "|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|" << std::endl
                  << "| 0 - exit                                     |" << std::endl
                  << "| 1 - print !A (not A)                         |" << std::endl
                  << "| 2 - print !B (not B)                         |" << std::endl
                  << "| 3 - print A ⋃ B (A union B)                  |" << std::endl
                  << "| 4 - print A ⋂ B (A intersection B)           |" << std::endl
                  << "| 5 - print A \\ B (A difference B)             |" << std::endl
                  << "| 6 - print B \\ A (B difference A)             |" << std::endl
                  << "| 7 - print A △ B (A symmetrical difference B) |" << std::endl
                  << "| 8 - print B △ A (B symmetrical difference A) |" << std::endl
                  << "| 9 - restart                                  |" << std::endl
                  << " ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ " << std::endl
                  << "Please, input number from 0 to 9: ";

        std::string s;
        getline(std::cin, s);

        // input check
        while (!is_number(s, 0, 9))
        {
            std::cout << "Please, try again: ";
            getline(std::cin, s);
        }

        switch (std::stoi(s))
        {
        case 0:
            is_end = true;

            break;
        case 1:
            std::cout << "!A:" << std::endl;
            (!A).print();
            std::cout << std::endl;

            break;
        case 2:
            std::cout << "!B:" << std::endl;
            (!B).print();
            std::cout << std::endl;

            break;
        case 3:
            std::cout << "A ⋃ B:" << std::endl;
            A.getUnion(B).print();
            std::cout << std::endl;

            break;
        case 4:
            std::cout << "A ⋂ B:" << std::endl;
            A.getIntersection(B).print();
            std::cout << std::endl;

            break;
        case 5:
            std::cout << "A \\ B:" << std::endl;
            (A.getDifference(B)).print();
            std::cout << std::endl;

            break;
        case 6:
            std::cout << "B \\ A:" << std::endl;
            (B.getDifference(A)).print();
            std::cout << std::endl;

            break;
        case 7:
            std::cout << "A △ B:" << std::endl;
            A.getSymmetricalDifference(B).print();
            std::cout << std::endl;

            break;
        case 8:
            std::cout << "B △ A:" << std::endl;
            B.getSymmetricalDifference(A).print();
            std::cout << std::endl;

            break;
        case 9:
            is_end = true;
            is_restart = true;

            break;
        default:
            break;
        }
    } while (!is_end);

    if (is_restart)
    {
        std::cout << "Restart." << std::endl;
        main_loop();
    }
    else
        std::cout << "End." << std::endl;
}

int main()
{
    srand(time(nullptr));

    main_loop();

    return 1;
}