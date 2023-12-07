#pragma once

#include "result.h"
#include "constexpr.h"

template<size_t N>
constexpr Result Compute(const char(&input)[N])
{
	Result retval{};

	// Card number means nothign so skip

	// Get the index to start consuming numbers from
	size_t winning_start = find_char(input, ':') + 1;

	// Get the index that marks the end of the winning numbers
	size_t winning_end = find_char(input, '|');

	// Have static storage for up to 15 nums although I think problem caps at 10
	size_t winning_nums[15]{};

	// Consume and store winning numbers:
	size_t tracker = winning_start;
	size_t winning_num = next_digit(input, tracker, winning_end);

	while (0 != winning_num)
	{
		// Store the winning num in the array
		for (size_t i = 0; i < 15; i++)
		{
			if (winning_nums[i] == 0)
			{
				winning_nums[i] = winning_num;
				break;
			}
		}

		// Get next winning num
		winning_num = next_digit(input, tracker, winning_end);
	}

	// Now get our nums
	size_t our_nums[30]{};

	size_t our_start = winning_end + 1;

	size_t our_end = N - 1;

	// Consume and store winning numbers:
	tracker = our_start;
	size_t our_num = next_digit(input, tracker, our_end);

	while (0 != our_num)
	{
		// Store the winning num in the array
		for (size_t i = 0; i < 30; i++)
		{
			if (our_nums[i] == 0)
			{
				our_nums[i] = our_num;
				break;
			}
		}

		// Get next winning num
		our_num = next_digit(input, tracker, our_end);
	}

	// Now we have two arrays of our nums and winning nums
	retval = calc_score(winning_nums, our_nums);

	return retval;
}
