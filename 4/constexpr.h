#pragma once

#include "result.h"

template<size_t N>
constexpr Result sum_results(const Result(&input)[N])
{
	Result ret{};

	for (int j = 0; j < N; j++)
	{
		ret.part1 += input[j].part1;
		ret.part2 += input[j].part2;
	}

	return ret;
}

template<size_t N>
constexpr size_t count_scratchcard(const Result(&input)[N], size_t index)
{
	// We have this copy
	size_t ret = 1;

	// Which won us
	size_t wins = input[index].part2;

	// For each
	for (int j = index + 1; j < index + 1 + wins; j++)
	{
		ret += count_scratchcard(input, j);
	}

	return ret;
}

template<size_t N>
constexpr size_t count_scratchcards(const Result(&input)[N])
{
	size_t ret = 0;

	// For each
	for (int j = 0; j < N; j++)
	{
		ret += count_scratchcard(input, j);
	}

	return ret;
}

template<size_t N>
constexpr size_t find_char(const char(&input)[N], char c)
{
	size_t ret = 0;

	for (size_t i = 0; i < N - 1; i++)
	{
		// Check for digit
		if (c == input[i])
		{
			ret = i;

			break;
		}
	}

	return ret;
}

template<size_t N, size_t M>
constexpr Result calc_score(const size_t(&winning_nums)[N], const size_t(&our_nums)[M])
{
	Result score{};

	// Iterate winning nums
	for (int i = 0; i < N; i++)
	{
		// Winning num end condition
		if (winning_nums[i] == 0)
		{
			break;
		}

		for (int j = 0; j < M; j++)
		{
			// Our nums end of array
			if (our_nums[j] == 0)
			{
				break;
			}

			if (our_nums[j] == winning_nums[i])
			{
				if (score.part1 == 0)
				{
					score.part1 = 1;
				}
				else
				{
					score.part1 *= 2;
				}

				score.part2 += 1;

				break;
			}
		}
	}

	return score;
}

template<size_t N>
constexpr size_t next_digit(const char(&input)[N], size_t& start_index, size_t bound)
{
	size_t ret = 0;

	for (size_t i = start_index; i < bound; i++)
	{
		// Check for digit
		if ('0' <= input[i] && input[i] <= '9')
		{
			// Hit digit, so grab all consecutive digits
			size_t j = i;

			while ('0' <= input[j] && input[j] <= '9')
			{
				ret *= 10;
				ret += (input[j] - '0');
				j++;
			}

			// Update start index
			start_index = j;

			break;
		}
	}

	return ret;
}
