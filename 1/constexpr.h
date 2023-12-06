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
constexpr bool find(const char* a, const char(&b)[N])
{
	bool ret = true;

	for (size_t i = 0; i < N-1; i++)
	{
		if (a[i] != b[i])
		{
			ret = false;
			break;
		}
	}

	return ret;
}