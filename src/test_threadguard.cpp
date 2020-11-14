#include "test_threadguard.hpp"
#include "threadguard.hpp"
#include <iostream>

namespace
{
	struct BackgroundTask
	{
	public:
		BackgroundTask(int &value) : m_value(value) {}
		
		void operator()()
		{
			++m_value;
		}

	private:
		int& m_value;
	};
}

void test_threadguard()
{
	int local_v = 42;
	BackgroundTask task(local_v);

	{
		std::thread t(task);
		ThreadGuard thread_guard(t);
	}

	std::cout << "local_v: " << local_v << std::endl;	// 43
}
