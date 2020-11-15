#include <iostream>
#include "start_thread.hpp"
#include "test_threadguard.hpp"
#include "test_scopedthread.hpp"

int main()
{
    //start_thread_1();
    //start_thread_2();
    //start_thread_3();
    //start_thread_with_param_1();
    //start_thread_with_param_2();
    //start_thread_with_param_3();
    //start_thread_by_obj_func();

    //test_threadguard();

    test_scopedthread();

    std::cout << "press Enter to exist..." << std::endl;
    std::cin.get();
}