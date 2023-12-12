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
constexpr void get_valid_overlaps(const size_t(&seeds)[N], rng(&inout)[M])
{
	size_t newoutTracker = 0;
	// The new output to write over the input
	rng newout[M]{};

	// For each viable range
	for (int i = 0; i < M; i++)
	{
		// Check for end of array
		if (inout[i].len == 0)
		{
			break;
		}

		// For each seed range
		for (int j = 0; j < N / 2; j++)
		{
			size_t start = seeds[2 * j];
			size_t len = seeds[2 * j + 1];

			if (start <= inout[i].start && inout[i].start <= (start + len))
			{
				/*
					The range starts within the target so the size is
					the lower of the map end or the range end
				*/
				size_t lenRange = (inout[i].start + inout[i].len) < (start + len) ? inout[i].len : (start + len - inout[i].start);

				// Portion of range that fits in map output is lenRange long starting at range start
				// So possible range is map input and len
				newout[newoutTracker] = { start + (inout[i].start - start),  lenRange };
				newoutTracker++;
			}
			else if (inout[i].start < start && start < (inout[i].start + inout[i].len))
			{
				/*
					The range starts before but finishes after so the size
					is the lower of the range end or the map end
				*/
				size_t lenRange = (inout[i].start + inout[i].len) < (start + len) ? (inout[i].start + inout[i].len - start) : (start + len - start);

				newout[newoutTracker] = { start,  lenRange };
				newoutTracker++;
			}
		}
	}

	for (int i = 0; i < newoutTracker; i++)
	{
		inout[i] = newout[i];
	}

	for (int i = newoutTracker; i < M; i++)
	{
		inout[i] = {};
	}
}

template<size_t N>
constexpr Result count_ranges(const rng(&ranges)[N])
{
	size_t i = 0;

	for (i = 0; i < N; i++)
	{
		if (ranges[i].len == 0)
		{
			break;
		}
	}

	return { 10, i };
}

template<size_t N, size_t M>
constexpr size_t get_valid_ranges(const size_t(&map)[N][3], rng(&inout)[M])
{
	size_t debug = 0;

	/*
		problem range 625635594, 1
	*/

	size_t newoutTracker = 0;
	// The new output to write over the input
	rng newout[M]{};

	rng additionalNewout[3 * M]{};
	size_t additionalNewoutTracker = 0;

	// For each target ouput
	for (int i = 0; i < M; i++)
	{
		// Create copy of inputs in bigger array
		additionalNewout[additionalNewoutTracker] = inout[i];
		additionalNewoutTracker++;

		// Check for end of array
		if (inout[i].len == 0)
		{
			break;
		}

		// For each mapping
		for (int j = 0; j < N; j++)
		{
			// For each map output

			/*
				Say for example we have a target output of 0->100 mill

				We want any map dest that overlaps with that

				We have 6 overlap cases
				- our range fits entirely within the map outout
				- our range starts inside but finishes outside
				- our range starts outside but finishes inside
				- our range starts before and ends after
				- our range starts and ends before
				- our range starts and ends after
			*/

			// We're first going to deal with anything that starts at or after
			// Map dest <= desired range start <= Map dest + size
			if (map[j][0] <= inout[i].start && inout[i].start <= (map[j][0] + map[j][2]))
			{
				/*
					The range starts within the target so the size is
					the lower of the map end or the range end
				*/
				size_t lenRange = (inout[i].start + inout[i].len) < (map[j][0] + map[j][2]) ? inout[i].len : (map[j][0] + map[j][2] - inout[i].start);

				// Portion of range that fits in map output is lenRange long starting at range start
				// So possible range is map input and len
				newout[newoutTracker] = { map[j][1] + (inout[i].start - map[j][0]),  lenRange};
				newoutTracker++;
			}
			else if (inout[i].start < map[j][0] && map[j][0] < (inout[i].start + inout[i].len))
			{
				/*
					The range starts before but finishes after so the size
					is the lower of the range end or the map end
				*/
				size_t lenRange = (inout[i].start + inout[i].len) < (map[j][0] + map[j][2]) ? (inout[i].start + inout[i].len - map[j][0]) : (map[j][0] + map[j][2] - map[j][0]);

				newout[newoutTracker] = { map[j][1],  lenRange };
				newoutTracker++;
			}
		}
	}


	// After we find all ranges that map into the target we also need to consider anything in the target range
	// that isn't mapped away by the mapping inputs

	/*
		Here we iterate over a copy of the target ranges
		
		For each target range we iterate over the map, if anything in the map
		source overlaps with the target then we know it gets mapped away
		so we add the new split range onto the end of the array we're iterating over
		so that those have a chance to be split again if necessary etc.

		We hope 3x is enough space but we'll see
	*/
	for (int i = 0; i < 3 * M; i++)
	{
		if (additionalNewout[i].len == 0)
		{
			break;
		}

		// For each map entry
		for (int j = 0; j < N; j++)
		{
			bool split = false;

			/*
				If the map starts within the target then its at least cut
				so the new possible range is from the target start up until the map
				start
			*/
			if (additionalNewout[i].start <= map[j][1] && map[j][1] <= (additionalNewout[i].start + additionalNewout[i].len))
			{
				if (map[j][1] - additionalNewout[i].start > 0)
				{
					additionalNewout[additionalNewoutTracker] = { additionalNewout[i].start, (map[j][1] - additionalNewout[i].start) };
					additionalNewoutTracker++;
					split = true;
				}
			}

			/*
				If the range ends within then we also have a slice that is the map end up until the target end
			*/
			if(additionalNewout[i].start <= (map[j][1] + map[j][2]) && (map[j][1] + map[j][2]) <= (additionalNewout[i].start + additionalNewout[i].len))
			{
				additionalNewout[additionalNewoutTracker] = { (map[j][1] + map[j][2]), ((additionalNewout[i].start + additionalNewout[i].len) - (map[j][1] + map[j][2])) };
				additionalNewoutTracker++;
				split = true;
			}
			
			// What about if the whole range is encompassed
			if (map[j][1] <= additionalNewout[i].start && additionalNewout[i].start <= (map[j][1] + map[j][2]))
			{
				// This range is obliterated so no new range to add but mark this as invalid
				split = true;
			}

			// If we split the range then the old one is no longer valid
			if (split)
			{
				additionalNewout[i] = {};
			}
		}
	}

	// Now migrate our results over to the inout
	size_t resCopyTracker = 0;

	for (int i = 0; i < newoutTracker; i++)
	{
		inout[resCopyTracker] = newout[i];
		resCopyTracker++;
	}

	for (int i = 0; i < additionalNewoutTracker; i++)
	{
		if (additionalNewout[i].len != 0)
		{
			inout[resCopyTracker] = additionalNewout[i];
			resCopyTracker++;
		}
	}

	for (int i = resCopyTracker; i < M; i++)
	{
		inout[i] = {};
	}

	return debug;
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