#pragma once

#include "result.h"
#include "constexpr.h"

template<size_t N>
constexpr Result Compute(const char(&input)[N])
{
	Result retval{};

	size_t COUNT = N - 1;

	/*
		PART 1
	*/

	size_t part1 = 0;

	// Walk forwards for first digit
	for (size_t i = 0; i < COUNT; i++)
	{
		// Check for digit
		if ('0' <= input[i] && input[i] <= '9')
		{
			// This is the first number so represents the tens column so add that to the retval
			part1 += 10 * (input[i] - '0');
			break;
		}
	}

	// Walk backwards for second digit
	for (size_t i = COUNT; i --> 0;)
	{
		// Check for digit
		if ('0' <= input[i] && input[i] <= '9')
		{
			// This is the second number so represents the ones column so add that to the retval
			part1 += (input[i] - '0');
			break;
		}
	}

	retval.part1 = part1;

	/*
		PART 2
	*/

	size_t part2 = 0;

	// Walk forwards for first digit
	for (size_t i = 0; i < COUNT; i++)
	{
		// Check for digit
		if ('0' <= input[i] && input[i] <= '9')
		{
			// This is the first number so represents the tens column so add that to the retval
			part2 += 10 * (input[i] - '0');
			break;
		}
		else if (find(&input[i], "one"))
		{
			part2 += 10 * 1;
			break;
		}
		else if (find(&input[i], "two"))
		{
			part2 += 10 * 2;
			break;
		}
		else if (find(&input[i], "three"))
		{
			part2 += 10 * 3;
			break;
		}
		else if (find(&input[i], "four"))
		{
			part2 += 10 * 4;
			break;
		}
		else if (find(&input[i], "five"))
		{
			part2 += 10 * 5;
			break;
		}
		else if (find(&input[i], "six"))
		{
			part2 += 10 * 6;
			break;
		}
		else if (find(&input[i], "seven"))
		{
			part2 += 10 * 7;
			break;
		}
		else if (find(&input[i], "eight"))
		{
			part2 += 10 * 8;
			break;
		}
		else if (find(&input[i], "nine"))
		{
			part2 += 10 * 9;
			break;
		}
		
	}

	for (size_t i = COUNT; i-- > 0;)
	{
		// Check for digit
		if ('0' <= input[i] && input[i] <= '9')
		{
			// This is the first number so represents the tens column so add that to the retval
			part2 += (input[i] - '0');
			break;
		}
		else if (find(&input[i], "one"))
		{
			part2 += 1;
			break;
		}
		else if (find(&input[i], "two"))
		{
			part2 += 2;
			break;
		}
		else if (find(&input[i], "three"))
		{
			part2 += 3;
			break;
		}
		else if (find(&input[i], "four"))
		{
			part2 += 4;
			break;
		}
		else if (find(&input[i], "five"))
		{
			part2 += 5;
			break;
		}
		else if (find(&input[i], "six"))
		{
			part2 += 6;
			break;
		}
		else if (find(&input[i], "seven"))
		{
			part2 += 7;
			break;
		}
		else if (find(&input[i], "eight"))
		{
			part2 += 8;
			break;
		}
		else if (find(&input[i], "nine"))
		{
			part2 += 9;
			break;
		}

	}

	retval.part2 = part2;

	
	return retval;
}