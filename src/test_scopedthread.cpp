#include "test_scopedthread.hpp"
#include "scopedthread.hpp"
#include <cassert>
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
        std::cout << "---> value: " << m_value << std::endl;
    }

private:
    int& m_value;
};
}

void test_scopedthread()
{
    int local_v = 42;
    BackgroundTask task(local_v);

    {
        std::thread t(task);
        ScopedThread scoped_thread(std::move(t));
    }

    assert(43 == local_v);
}