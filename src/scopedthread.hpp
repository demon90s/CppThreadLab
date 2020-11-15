#pragma once

#include <thread>

class ScopedThread
{
public:
    explicit ScopedThread(std::thread t) :
        m_t(std::move(t))
    {
        if (!m_t.joinable())
        {
            throw std::logic_error("ScopedThread::ScopedThread(), No thread");
        }
    }
    ~ScopedThread()
    {
        m_t.join();
    }
    ScopedThread(const ScopedThread &) = delete;
    ScopedThread &operator=(const ScopedThread &) = delete;

private:
    std::thread m_t;
};