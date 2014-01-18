#pragma once

#include <algorithm>
#include <random>

namespace algorithm
{
	template <class RandomIt>
	void bogosort(RandomIt begin, RandomIt end)
	{
		std::random_device rd;
		std::mt19937 engine(rd());

		while (!std::is_sorted(begin, end))
			std::shuffle(begin, end, engine);
	};
}