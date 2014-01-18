#include "algorithm.h"
#include <vector>
#include <iostream>
#include "quicksort.h"
#include "shellsort.h"

#include <chrono>


template <class T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec)
{
	for (auto&& elem : vec)
		stream << elem << " ";
	stream << std::endl;
	return stream;
}

int main()
{
	auto vec1 = algorithm::make_random_vector(std::numeric_limits<int>::min(),std::numeric_limits<int>::max(), 10);
	auto vec2 = vec1;
	auto vec3 = vec1;
	auto vec4 = vec1;

	std::vector<int> arr = { 10, 15, 20, 14 ,  5 };

	long long shortest = std::numeric_limits<long long>::max();
	int shortest_num = 0;

	algorithm::Timer clock;
	
	algorithm::quicksort(vec1.begin(), vec1.end());
	long long time1 = clock.reset();
	algorithm::parallel_quicksort(vec2.begin(), vec2.end());
	long long time2 = clock.reset();
	algorithm::introsort(vec3.begin(), vec3.end());
	long long time3 = clock.reset();
	std::sort(vec4.begin(), vec4.end());
	long long time4 = clock.reset();
	if (!std::is_sorted(vec3.begin(), vec3.end()))
		std::cout << "INTROSORT FAILED!" << std::endl;

	std::cout << "quicksort: " << time1 << std::endl;
	std::cout << "parallel quicksort: " << time2 << std::endl;;
	std::cout << "parallel introsort: " << time3 << std::endl;;
	std::cout << "std::sort: " << time4 << std::endl;;

	std::cout << std::endl;
}