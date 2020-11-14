#include "start_thread.hpp"
#include <thread>
#include <string>
#include <iostream>

namespace
{
	void do_some_work()
	{

	}
}

void start_thread_1()
{
	std::thread t(do_some_work);
	//t.join();
	t.detach();
	// 如果不调用 join 或分离方法，thread的析构函数会调用 std;:terminate 终止程序
}

namespace
{
	struct BackgroundTask
	{
	public:
		void operator()()
		{

		}
	private:
		void do_some_work()
		{

		}
	};
}
void start_thread_2()
{
	BackgroundTask task;
	std::thread t(task);
	t.join();
}

void start_thread_3()
{
	std::thread t([]() { do_some_work(); });
	t.join();
}

namespace
{
	void do_some_work_by_param(std::string& str)
	{
		str = "do_some_work_by_param";
	}
}

void start_thread_with_param_1()
{
	std::string str = "hello";
	
	std::thread t(do_some_work_by_param, str);
	t.join();
	
	std::cout << "str: " << str << std::endl;	// 仍旧是 hello, 这是因为在这里str会拷贝给线程的内部存储空间，然后内存存储的数据传给处理函数
}

void start_thread_with_param_2()
{
	std::string str = "hello";

	std::thread t(do_some_work_by_param, std::ref(str));
	t.join();

	std::cout << "str: " << str << std::endl;	// do_some_work_by_param
}