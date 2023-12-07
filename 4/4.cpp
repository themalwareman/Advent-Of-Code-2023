// 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "input.h"
#include "compute.h"
#include "constexpr.h"

/*
    On MSVC you need to update the constexpr limits and compiler
    because the recursion for part 2 is too difficult for intellisense.

    I set them to huge numbers i.e. /constexpr:depth20000 /constexpr:steps100000000 

    And it compiled after about 1 minute.
*/
int main()
{
    constexpr Result puzzle_four = sum_results(input);

    constexpr size_t num = count_scratchcards(input);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
