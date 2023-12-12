#pragma once

#include "result.h"
#include "constexpr.h"
#include "input.h"

#include <stdlib.h>


template<size_t N>
constexpr Result Compute(const size_t(&input)[N])
{
	Result retval{};
	/*
		Part 1
	*/

	size_t seed_locations[N]{};

	// Seed soil fertilizer water light temperature humidity location
	size_t lowest_loc = -1;

	// For each seed
	for (int i = 0; i < N; i++)
	{
		size_t soil = map_to_next(input[i], seed_to_soil);
		size_t fert = map_to_next(soil, soil_to_fertilizer);
		size_t water = map_to_next(fert, fertilizer_to_water);
		size_t light = map_to_next(water, water_to_light);
		size_t temp = map_to_next(light, light_to_temperature);
		size_t humid = map_to_next(temp, temperature_to_humidity);
		size_t loc = map_to_next(humid, humidity_to_location);

		if (loc < lowest_loc)
		{
			lowest_loc = loc;
		}

		seed_locations[i] = loc;
	}

	retval.part1 = lowest_loc;

	/*
		Part 2
	*/

	/*
		The problem with the input is it has a lot of seed inputs to try, one solution we can try though
		is back tracing from location through the maps in reverse to see if the seed number exists.

		We can start with 1 through the lowest location range, then walk up through the location ranges in
		order until we find a seed that works

		Sadly this uses too much memory doing constexpr things.

		One solution is maybe to sample some seeds forward to find a low-ish location that
		then cuts down our reverse search upper bound.

		Okay, so we have an issue even trying the values 1 -> 10 million because everything is
		computed in ram as we aren't actually running code. So even though this code doesn't
		copy anything we still causes issues

		We know we want a value in the location output range 0->63 mill
		For this range we know all the humidities that would map to the input range for this output
		We can then scan the humidity outputs of the temperature_to_humidity map to see which temps
		are plausible and walk back to eventually find input seed ranges, then just see if any of the ranges overlap
		with a seed input and try those inputs
	*/

	rng valid_ranges[1000]{};

	// Set our target ouput
	valid_ranges[0] = { 0, 10'000'000 };

	// Back propagate the ranges
	get_valid_ranges(humidity_to_location, valid_ranges);
	get_valid_ranges(temperature_to_humidity, valid_ranges);
	get_valid_ranges(light_to_temperature, valid_ranges);
	get_valid_ranges(water_to_light, valid_ranges);
	get_valid_ranges(fertilizer_to_water, valid_ranges);
	get_valid_ranges(soil_to_fertilizer, valid_ranges);
	get_valid_ranges(seed_to_soil, valid_ranges);

	// Get valid overlaps of seed ranges and viable inputs
	get_valid_overlaps(seeds, valid_ranges);


	size_t lowest_loc_2 = -1;
	size_t low_seed = 0;

	// For each seed range output
	for (int i = 0; i < 1000; i++)
	{
		// Break when we hit the end
		if (valid_ranges[i].len == 0)
		{
			break;
		}

		// We need only to consider the seed at the bottom end of the range
		size_t seed = valid_ranges[i].start;

		size_t soil = map_to_next(seed, seed_to_soil);
		size_t fert = map_to_next(soil, soil_to_fertilizer);
		size_t water = map_to_next(fert, fertilizer_to_water);
		size_t light = map_to_next(water, water_to_light);
		size_t temp = map_to_next(light, light_to_temperature);
		size_t humid = map_to_next(temp, temperature_to_humidity);
		size_t loc = map_to_next(humid, humidity_to_location);

		if (loc < lowest_loc_2)
		{
			lowest_loc_2 = loc;
			low_seed = seed;
		}

		
	}

	retval.part2 = lowest_loc_2;

	return retval;
}

/*
/*
			Is there a gap betrween the last range and this one, if so
			we need to try those too
		/

for (size_t j = curr_max; j < search.dest; j++)
{
	// Try back propagate
	size_t loc = j;

	size_t humid = map_to_prev(loc, humidity_to_location);
	size_t temp = map_to_prev(humid, temperature_to_humidity);
	size_t light = map_to_prev(temp, light_to_temperature);
	size_t water = map_to_prev(light, water_to_light);
	size_t fert = map_to_prev(water, fertilizer_to_water);
	size_t soil = map_to_prev(fert, soil_to_fertilizer);
	size_t seed = map_to_prev(soil, seed_to_soil);

	if (seed_in_input(seed, input))
	{
		result = seed;
		result_loc = j;
		break;
	}
}

if (result != 0)
{
	break;
}

// Start by searching range
for (size_t j = search.dest; j < search.dest + search.len; j++)
{
	// Try back propagate
	size_t loc = j;

	size_t humid = map_to_prev(loc, humidity_to_location);
	size_t temp = map_to_prev(humid, temperature_to_humidity);
	size_t light = map_to_prev(temp, light_to_temperature);
	size_t water = map_to_prev(light, water_to_light);
	size_t fert = map_to_prev(water, fertilizer_to_water);
	size_t soil = map_to_prev(fert, soil_to_fertilizer);
	size_t seed = map_to_prev(soil, seed_to_soil);

	if (seed_in_input(seed, input))
	{
		result = seed;
		result_loc = j;
		break;
	}
}

if (result != 0)
{
	break;
}

curr_max = search.dest + search.len;
*/