#pragma once

#include <thread>

class ThreadGuard
{
public:
	explicit ThreadGuard(std::thread &t) : m_t(t) {}
	~ThreadGuard()
	{
		if (m_t.joinable())
		{
			m_t.join();
		}
	}

	ThreadGuard(const ThreadGuard&) = delete;
	ThreadGuard& operator=(const ThreadGuard&) = delete;

private:
	std::thread& m_t;
};