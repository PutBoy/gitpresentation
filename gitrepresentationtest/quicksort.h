#pragma once

#include "shellsort.h"
#include <functional>
#include <cmath>
#include <algorithm>
#include <future>

namespace algorithm
{
	namespace detail
	{
		template <class RandomAccessIterator>
		void cheat_heap_sort(RandomAccessIterator begin, RandomAccessIterator end)
		{
			std::make_heap(begin, end);
			std::sort_heap(begin, end);
		}

		template <class RandomAccessIterator>
		auto maxa(RandomAccessIterator a, RandomAccessIterator b)->RandomAccessIterator
		{
			//use < instead of > as stl prefers to force operator< on types 
			//rather than operator>
			return (*a<*b) ? b : a;
		}

		template <class RandomAccessIterator>
		auto median3_1_gt_2(RandomAccessIterator first, RandomAccessIterator mid, RandomAccessIterator last)->RandomAccessIterator
		{
			if (*first < *last) {
				return first;
			}
			else {
				return maxa(mid, last);
			}
		}
		
		template <class RandomAccessIterator>
		auto median3(RandomAccessIterator begin, RandomAccessIterator mid, RandomAccessIterator end)->RandomAccessIterator
		{
			if (begin == end)
				return begin;

			if (*mid<*begin) {
				return median3_1_gt_2(begin, mid, end - 1);
			}
			else {
				return median3_1_gt_2(mid, begin, end - 1);
			}
		}

		template <class RandomAccessIterator>
		auto get_pivot(RandomAccessIterator begin, RandomAccessIterator end)->RandomAccessIterator
		{
			RandomAccessIterator mid = begin + std::distance(begin, end) / 2;
			return median3(begin, mid, end);
		}


		template <class RandomAccessIterator>
		auto partition(RandomAccessIterator begin,
			RandomAccessIterator end,
			RandomAccessIterator pivot) -> RandomAccessIterator
		{
			if (begin == end)
				return begin;

			auto pivotVal = *pivot;
			std::swap(*pivot, *(end - 1));
			RandomAccessIterator store = begin;
			while (begin != end - 1)
			{
				if (*begin < pivotVal)
				{
					std::swap(*begin, *store);
					store++;
				}

				++begin;
			}

			std::swap(*store, *(end - 1));
			return store;
		}

		template <class RandomAccessIterator>
		void quicksort(RandomAccessIterator begin, RandomAccessIterator end,
			std::function<void(RandomAccessIterator, RandomAccessIterator)> secondary,
			int breakoff)
		{
			if ((begin - end) < (end - begin))
			{
				if (std::distance(begin, end) < breakoff)
					secondary(begin, end);
				else
				{
					auto pivot = detail::get_pivot(begin, end);
					auto pivotVal = *pivot;
					pivot = detail::partition(begin, end, pivot);

					quicksort(begin, pivot, secondary, breakoff);
					quicksort(pivot + 1, end, secondary, breakoff);
				}
			}
		}

		template <class RandomAccessIterator>
		void parallel_quicksort(RandomAccessIterator begin, RandomAccessIterator end,
			std::function<void(RandomAccessIterator, RandomAccessIterator)> secondary,
			int breakoff)
		{
			if ((begin - end) < (end - begin))
			{
				if (std::distance(begin, end) < breakoff)
					secondary(begin, end);
				else
				{
					auto pivot = detail::get_pivot(begin, end);
					auto pivotVal = *pivot;
					pivot = detail::partition(begin, end, pivot);

					auto future = std::async(std::launch::async, quicksort<RandomAccessIterator>, begin, pivot, secondary, breakoff);
					quicksort(pivot + 1, end, secondary, breakoff);
					future.wait();
				}
			}
		}
	}

	//driver
	template <class RandomAccessIterator>
	void quicksort(RandomAccessIterator begin, RandomAccessIterator end, 
		std::function<void(RandomAccessIterator, RandomAccessIterator)> secondary = 
			std::function<void(RandomAccessIterator, RandomAccessIterator)>(&shellsort<RandomAccessIterator>),
		int breakoff = 7)
	{
		if (breakoff < 0)
			detail::quicksort(begin, end, secondary, static_cast<int>(std::log2(std::distance(begin, end))));
		else
			detail::quicksort(begin, end, secondary, breakoff);
	}

	
	//driver
	template <class RandomAccessIterator>
	void parallel_quicksort(RandomAccessIterator begin, RandomAccessIterator end,
		std::function<void(RandomAccessIterator, RandomAccessIterator)> secondary =
		std::function<void(RandomAccessIterator, RandomAccessIterator)>(&shellsort<RandomAccessIterator>),
		int breakoff = 7)
	{
		if (breakoff < 0)
			detail::parallel_quicksort(begin, end, secondary, static_cast<int>(std::log2(std::distance(begin, end))));
		else
			detail::parallel_quicksort(begin, end, secondary, breakoff);
	}

	template <class RandomAccessIterator>
	void introsort(RandomAccessIterator begin, RandomAccessIterator end)
	{
 		detail::parallel_quicksort(begin, end, std::function<void(RandomAccessIterator, RandomAccessIterator)>(&detail::cheat_heap_sort<RandomAccessIterator>), static_cast<int>(std::log2(std::distance(begin, end))));
	}
}