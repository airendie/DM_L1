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
        std::cout << "╒═══════════════════════════════════════════════════╕" << std::endl
                  << "│                       Menu:                       │" << std::endl
                  << "╞═══════════════════════════════════════════════════╡" << std::endl
                  << "│ 0  - exit                                         │" << std::endl
                  << "│ 1  - restart                                      │" << std::endl
                  << "╞═══════════════════════════════════════════════════╡" << std::endl
                  << "│ 2  - print A                                      │" << std::endl
                  << "│ 3  - print B                                      │" << std::endl
                  << "│ 4  - print !A (not A)                             │" << std::endl
                  << "│ 5  - print !B (not B)                             │" << std::endl
                  << "│ 6  - print A ⋃ B (A union B)                      │" << std::endl
                  << "│ 7  - print A ⋂ B (A intersection B)               │" << std::endl
                  << "│ 8  - print A \\ B (A difference B)                 │" << std::endl
                  << "│ 9  - print B \\ A (B difference A)                 │" << std::endl
                  << "│ 10 - print A △ B (A symmetric addition B)         │" << std::endl
                  << "│ 11 - print B △ A (B symmetric addition A)         │" << std::endl
                  << "│ 12 - print A + B (A arithmectic plus B)           │" << std::endl
                  << "│ 13 - print A - B (A arithmectic difference B)     │" << std::endl
                  << "│ 14 - print B - A (B arithmectic difference A)     │" << std::endl
                  << "│ 15 - print A * B (A arithmectic multiplication B) │" << std::endl
                  << "│ 16 - print A / B (A arithmectic division B)       │" << std::endl
                  << "│ 17 - print B / A (B arithmectic division A)       │" << std::endl
                  << "╘═══════════════════════════════════════════════════╛" << std::endl
                  << "Please, input number from 0 to 17: ";

        std::string s;
        getline(std::cin, s);

        // input check
        while (!is_number(s, 0, 17))
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
            is_end = true;
            is_restart = true;

            break;
        case 2:
            std::cout << "A:" << std::endl;
            A.print();
            std::cout << std::endl;

            break;
        case 3:
            std::cout << "B:" << std::endl;
            B.print();
            std::cout << std::endl;

            break;
        case 4:
            std::cout << "!A:" << std::endl;
            (!A).print();
            std::cout << std::endl;

            break;
        case 5:
            std::cout << "!B:" << std::endl;
            (!B).print();
            std::cout << std::endl;

            break;
        case 6:
            std::cout << "A ⋃ B:" << std::endl;
            A.getUnion(B).print();
            std::cout << std::endl;

            break;
        case 7:
            std::cout << "A ⋂ B:" << std::endl;
            A.getIntersection(B).print();
            std::cout << std::endl;

            break;
        case 8:
            std::cout << "A \\ B:" << std::endl;
            A.getDifference(B).print();
            std::cout << std::endl;

            break;
        case 9:
            std::cout << "B \\ A:" << std::endl;
            B.getDifference(A).print();
            std::cout << std::endl;

            break;
        case 10:
            std::cout << "A △ B:" << std::endl;
            A.getSymmetricDifference(B).print();
            std::cout << std::endl;

            break;
        case 11:
            std::cout << "B △ A:" << std::endl;
            B.getSymmetricDifference(A).print();
            std::cout << std::endl;

            break;
        case 12:
            std::cout << "A + B:" << std::endl;
            (A + B).print();
            std::cout << std::endl;

            break;
        case 13:
            std::cout << "A - B:" << std::endl;
            (A - B).print();
            std::cout << std::endl;

            break;
        case 14:
            std::cout << "B - A:" << std::endl;
            (B - A).print();
            std::cout << std::endl;

            break;
        case 15:
            std::cout << "A * B:" << std::endl;
            (A * B).print();
            std::cout << std::endl;

            break;
        case 16:
            std::cout << "A / B:" << std::endl;
            (A / B).print();
            std::cout << std::endl;

            break;
        case 17:
            std::cout << "B / A:" << std::endl;
            (B / A).print();
            std::cout << std::endl;

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