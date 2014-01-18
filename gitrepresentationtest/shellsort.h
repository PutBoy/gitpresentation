#pragma once

namespace algorithm
{
	template <class RandomIt>
	void shellsort(RandomIt begin, RandomIt end)
	{
		int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
		int len = std::distance(begin, end);
		for (auto gap : gaps)
		{
			for (int i = gap; i < len; ++i)
			{
				auto temp = *(begin + i);
				int j = i;
				for (; j >= gap && *(begin + j - gap) > temp; j -= gap)
				{
					*(begin + j) = *(begin + j - gap);
				}
				*(begin + j) = temp;
			}

		}
	}
}