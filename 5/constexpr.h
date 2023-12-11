#pragma once


template<size_t N>
constexpr size_t map_to_next(size_t input, const size_t(&map)[N][3])
{
	// Default is same number but will change if found in a mapping
	size_t ret = input;


	// Dest, src, len
	for (int i = 0; i < N; i++)
	{
		if (input >= map[i][1] && input < (map[i][1] + map[i][2]))
		{
			// Found a mapping
			ret = map[i][0] + (input - map[i][1]);

			break;
		}
	}

	return ret;
}

struct rng
{
	size_t start;
	size_t len;
};

template<size_t N, size_t M>
constexpr void get_valid_ranges(const size_t(&map)[N][3], rng(&inout)[M])
{
	// The new output to write over the input
	rng newout[M]{};

	// Default is same number but will change if found in a mapping
	size_t ret = input;


	// Dest, src, len
	for (int i = 0; i < N; i++)
	{
		if (input >= map[i][0] && input < (map[i][0] + map[i][2]))
		{
			// Found a mapping
			ret = map[i][1] + (input - map[i][0]);

			break;
		}
	}

	return ret;
}

template<size_t N>
constexpr size_t map_to_prev(size_t input, const size_t(&map)[N][3])
{
	// Default is same number but will change if found in a mapping
	size_t ret = input;


	// Dest, src, len
	for (int i = 0; i < N; i++)
	{
		if (input >= map[i][0] && input < (map[i][0] + map[i][2]))
		{
			// Found a mapping
			ret = map[i][1] + (input - map[i][0]);

			break;
		}
	}

	return ret;
}

template<size_t N>
constexpr bool seed_in_input(size_t seed, const size_t(&seeds)[N])
{
	bool ret = false;

	for (int i = 0; i < N / 2; i++)
	{
		if (seed >= seeds[2 * i] && seed < seeds[2 * i] + seeds[2 * i + 1])
		{
			ret = true;
			break;
		}
	}

	return ret;
}

struct Range
{
	size_t dest;
	size_t src;
	size_t len;
};

template<size_t N>
constexpr Range get_next_lowest(size_t& curr, const size_t(&ranges)[N][3])
{
	Range ret{-1, -1, -1};

	for (int i = 0; i < N; i++)
	{
		// If dest is bigger than or equal to curr
		// and less than current stored ret range
		if (ranges[i][0] >= curr && ranges[i][0] < ret.dest)
		{
			ret = { ranges[i][0], ranges[i][1] , ranges[i][2] };
		}
	}

	// Update curr so next time we get called it chooses the next lowest range
	curr = ret.dest + 1;

	return ret;
}