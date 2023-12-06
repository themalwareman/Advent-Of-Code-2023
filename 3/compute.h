#pragma once

#include "result.h"
#include "constexpr.h"

template<size_t X, size_t Y>
constexpr Result Compute(const char(&input)[Y][X])
{
	Result retval{};

	// Trim off the null term on the input strings for iterating
	size_t x = X - 1;
	size_t y = Y;

	/*
		Part 1
	*/

	size_t sum = 0;

	// For each row
	for (size_t i = 0; i < y; i++)
	{
		// Get the first num
		size_t tracker = 0;

		size_t num = next_digit(input[i], tracker);

		bool partNumber = false;

		while (num != 0)
		{
			// Check to see if we have an adjacent symbol

			/*
				Checking for an adjacent symbol means
				checking for a non '.' character in indexes

				tracker - 1
				through
				tracker + num_digits

				both above and below
			*/
			size_t num_digits = digits(num);

			size_t num_start_index = tracker - num_digits;

			if (num_start_index != 0 && input[i][num_start_index - 1] != '.')
			{
				partNumber = true;
			}
			else if (num_start_index + num_digits < x && input[i][num_start_index + num_digits] != '.')
			{
				partNumber = true;
			}
			else
			{
				if (i > 0)
				{
					size_t startBound = num_start_index;

					if (num_start_index > 0)
					{
						startBound -= 1;
					}

					size_t endBound = num_start_index + num_digits;

					if (endBound < x - 1)
					{
						endBound += 1;
					}


					for (size_t j = startBound; j < endBound; j++)
					{
						if (input[i - 1][j] != '.')
						{
							partNumber = true;
							break;
						}
					}
				}	

				if (i < y-1)
				{
					size_t startBound = num_start_index;

					if (num_start_index > 0)
					{
						startBound -= 1;
					}

					size_t endBound = num_start_index + num_digits;

					if (endBound < x - 1)
					{
						endBound += 1;
					}


					for (size_t j = startBound; j < endBound; j++)
					{
						if (input[i + 1][j] != '.')
						{
							partNumber = true;
							break;
						}
					}
				}

			}
			
			if (partNumber)
			{
				sum += num;
			}

			// Load next digit
			num = next_digit(input[i], tracker);
			
			// Reset bool
			partNumber = false;
		}
	}

	retval.part1 = sum;

	/*
		Part 2
	*/

	size_t sum_ratios = 0;

	// For each row
	for (size_t i = 0; i < y; i++)
	{

		bool isGear = false;

		size_t tracker = 0;

		size_t postIndex = next_cog(input[i], tracker);

		while (postIndex != 0)
		{

			// Save coords of 2 numbers if we find them
			int ix = -1;
			int iy = -1;
			int jx = -1;
			int jy = -1;

			size_t trueIndex = postIndex - 1;

			size_t xStartBound = trueIndex;

			if (trueIndex > 0)
			{
				xStartBound -= 1;
			}

			size_t xEndBound = trueIndex;

			if (xEndBound < x - 1)
			{
				xEndBound += 1;
			}

			// Search line above if possible
			if (i > 0)
			{
				bool digitFound = false;

				for (size_t j = xStartBound; j <= xEndBound; j++)
				{
					// Is this value a digit and we're not walking through one
					if (is_digit(input[i - 1], j) && digitFound == false)
					{
						digitFound = true;

						// Yes! Let's store it
						if (ix == -1)
						{
							ix = j;
							iy = i - 1;
						}
						else
						{
							jx = j;
							jy = i - 1;
						}
					}
					else if (not is_digit(input[i - 1], j))
					{
						// Not a digit, reset digit found
						digitFound = false;
					}
				}
			}

			// Search left
			if (trueIndex > 0 && is_digit(input[i], trueIndex - 1))
			{
				// Found a number! Let's store it
				if (ix == -1)
				{
					ix = trueIndex - 1;
					iy = i;
				}
				else
				{
					jx = trueIndex - 1;
					jy = i;
				}
			}

			// Search right
			if (trueIndex < x-1 && is_digit(input[i], trueIndex + 1))
			{
				// Found a number! Let's store it
				if (ix == -1)
				{
					ix = trueIndex + 1;
					iy = i;
				}
				else
				{
					jx = trueIndex + 1;
					jy = i;
				}
			}

			// Search below if possible
			if (i < y-1)
			{
				bool digitFound = false;

				for (size_t j = xStartBound; j <= xEndBound; j++)
				{
					// Is this value a digit and we're not walking through one
					if (is_digit(input[i+1], j) && digitFound == false)
					{
						digitFound = true;

						// Yes! Let's store it
						if (ix == -1)
						{
							ix = j;
							iy = i + 1;
						}
						else
						{
							jx = j;
							jy = i + 1;
						}
					}
					else if(not is_digit(input[i + 1], j))
					{
						// Not a digit, reset digit found
						digitFound = false;
					}
				}
			}

			// Did we find 2 values?
			if (ix != -1 && jx != -1)
			{
				size_t first = grab_num(input[iy], ix);

				size_t second = grab_num(input[jy], jx);

				size_t ratio = first * second;

				sum_ratios += ratio;
			}


			// Load next digit
			postIndex = next_cog(input[i], tracker);

			// Reset bool
			isGear = false;
		}
	}

	retval.part2 = sum_ratios;


	return retval;
}