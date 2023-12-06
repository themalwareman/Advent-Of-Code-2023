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

	size_t redCount = 12;
	size_t blueCount = 14;
	size_t greenCount = 13;

	// Grab a tracker to walk over input
	size_t tracker = 0;

	// Get the game id as the first number
	size_t gameId = next_digit(input, tracker);


	size_t num = next_digit(input, tracker);

	bool error = false;

	while (num != 0)
	{
		if (find(&input[tracker + 1], "red") && num > 12)
		{
			error = true;
		}
		else if (find(&input[tracker + 1], "green") && num > 13)
		{
			error = true;
		}
		else if (find(&input[tracker + 1], "blue") && num > 14)
		{
			error = true;
		}

		// Load next digit
		num = next_digit(input, tracker);
	}

	if (not error)
	{
		retval.part1 = gameId;
	}

	/*
		PART 2
	*/

	size_t minRed = 0;
	size_t minBlue = 0;
	size_t minGreen = 0;

	tracker = 0;
	gameId = next_digit(input, tracker);

	num = next_digit(input, tracker);

	while (num != 0)
	{
		// Check to see if min needs updating
		if (find(&input[tracker + 1], "red") && num > minRed)
		{
			minRed = num;
		}
		else if (find(&input[tracker + 1], "green") && num > minGreen)
		{
			minGreen = num;
		}
		else if (find(&input[tracker + 1], "blue") && num > minBlue)
		{
			minBlue = num;
		}

		// Load next digit
		num = next_digit(input, tracker);
	}

	size_t power = minRed * minGreen * minBlue;

	retval.part2 = power;

	return retval;
}