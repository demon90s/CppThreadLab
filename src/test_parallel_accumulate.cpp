#include "parallel_accumulate.hpp"
#include <iostream>

void test_parallel_accumulate()
{
	std::vector<int> vec;
	for (int i = 1; i <= 100; i++)
	{
		vec.push_back(i);
	}

	int res = parallel_accumulate(vec.begin(), vec.end(), 0);
	std::cout << res << std::endl;

	res = parallel_accumulate(vec.end(), vec.end(), 0);
	std::cout << res << std::endl;

	res = parallel_accumulate(vec.begin(), vec.end(), -5050);
	std::cout << res << std::endl;
}