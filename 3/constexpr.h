#pragma once

constexpr size_t digits(size_t number)
{
	size_t digits = 0;

	while (number)
	{
		number /= 10;
		digits++;
	}

	return digits;
}

template<size_t N>
constexpr bool is_digit(const char(&input)[N], size_t index)
{
	bool isDigit = false;

	if ('0' <= input[index] && input[index] <= '9')
	{
		isDigit = true;
	}

	return isDigit;
}

template<size_t N>
constexpr size_t grab_num(const char(&input)[N], size_t index)
{
	size_t ret = 0;

	size_t tracker = index;

	// Walk back to start of num
	while (('0' <= input[tracker] && input[tracker] <= '9') && ('0' <= input[tracker - 1] && input[tracker - 1] <= '9'))
	{
		tracker--;
	}

	// Now read
	// Hit digit, so grab all consecutive digits
	while ('0' <= input[tracker] && input[tracker] <= '9')
	{
		ret *= 10;
		ret += (input[tracker] - '0');
		tracker++;
	}

	return ret;
}


template<size_t N>
constexpr size_t next_digit(const char(&input)[N], size_t& start_index)
{
	size_t ret = 0;

	for (size_t i = start_index; i < N - 1; i++)
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

template<size_t N>
constexpr size_t next_cog(const char(&input)[N], size_t& start_index)
{
	size_t ret = 0;

	for (size_t i = start_index; i < N - 1; i++)
	{
		// Check for digit
		if ('*' == input[i])
		{
			ret = i+1;

			// Update start index
			start_index = i+1;

			break;
		}
	}

	return ret;
}