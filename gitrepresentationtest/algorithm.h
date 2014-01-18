#pragma once

#include <vector>
#include <random>
#include "bogosort.h"
#include "shellsort.h"
#include <type_traits>
#include <chrono>
namespace algorithm
{
	class Timer
	{
	public:
		Timer()
			:start_(std::chrono::system_clock::now())
		{}

		long long get_ms()
		{
			auto now = std::chrono::system_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds>(now - start_).count();
		}

		long long reset()
		{
			auto get = get_ms();
			start_ = std::chrono::system_clock::now();
			return get;
		}

		std::chrono::time_point<std::chrono::system_clock> start_;

	};

	template <class RandomIt>
	void default_sort(RandomIt begin, RandomIt end)
	{
		return shellsort(begin, end);
	}

	auto make_random_vector
		(unsigned char min, unsigned char max, int size)
		->std::vector<unsigned char>
	{
		std::mt19937 engine;
		std::uniform_int_distribution<int> dist(min, max);
		std::vector<unsigned char> ret(size);
		for (auto& val : ret)
			val = static_cast<char>(dist(engine));
		return std::move(ret);
	}

	auto make_random_vector
		(char min, char max, int size)
		->std::vector<char>
	{
		std::mt19937 engine;
		std::uniform_int_distribution<int> dist(min, max);
		std::vector<char> ret(size);
		for (auto& val : ret)
			val = static_cast<char>(dist(engine));
		return std::move(ret);
	}

	template <class T>
	auto make_random_vector
		(T min, T max, int size) 
			-> std::vector<typename std::enable_if<std::is_integral<T>::value, T>::type>
	{
		std::mt19937 engine;
		std::uniform_int_distribution<T> dist(min, max);
		std::vector<T> ret(size);
		for (auto& val : ret)
			val = dist(engine);
		return std::move(ret);
	}

	template <class T>
	auto make_random_vector
		(T min, T max, int size)
		-> std::vector<typename std::enable_if<std::is_floating_point<T>::value, T>::type>
	{
		std::mt19937 engine;
		std::uniform_real_distribution<T> dist(min, max);
		std::vector<T> ret(size);
		for (auto& val : ret)
			val = dist(engine);
		return std::move(ret);
	}

}