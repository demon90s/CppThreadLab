#include <iostream>
#include "start_thread.hpp"
#include "test_threadguard.hpp"

int main()
{
	//start_thread_1();
	//start_thread_2();
	//start_thread_3();
	//start_thread_with_param_1();
	start_thread_with_param_2();

	//test_threadguard();

	std::cout << "press Enter to exist..." << std::endl;
	std::cin.get();
}