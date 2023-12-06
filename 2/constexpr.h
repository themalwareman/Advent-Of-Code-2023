#pragma once


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
constexpr size_t next_digit(const char(&input)[N], size_t& start_index)
{
	size_t ret = 0;

	for (size_t i = start_index; i < N-1; i++)
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
constexpr bool find(const char* a, const char(&b)[N])
{
	bool ret = true;

	for (size_t i = 0; i < N - 1; i++)
	{
		if (a[i] != b[i])
		{
			ret = false;
			break;
		}
	}

	return ret;
}