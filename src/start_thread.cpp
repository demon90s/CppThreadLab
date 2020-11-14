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
	// ��������� join ����뷽����thread��������������� std;:terminate ��ֹ����
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
	
	std::cout << "str: " << str << std::endl;	// �Ծ��� hello, ������Ϊ������str�´�����̵߳��ڲ��洢�ռ䣬Ȼ���ڴ�洢�����ݴ���������
}

void start_thread_with_param_2()
{
	std::string str = "hello";

	std::thread t(do_some_work_by_param, std::ref(str));
	t.join();

	std::cout << "str: " << str << std::endl;	// do_some_work_by_param
}