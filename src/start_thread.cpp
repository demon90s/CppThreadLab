#include "start_thread.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>

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
    std::thread t([]() {
        do_some_work();
    });
    t.join();
}

namespace
{
void do_some_work_by_param(std::string& str)
{
    str = "do_some_work_by_param";
}
}

#ifndef __unix
// ��δ�����Linux�±��벻ͨ��
void start_thread_with_param_1()
{
    std::string str = "hello";

    std::thread t(do_some_work_by_param, str);
    t.join();

    std::cout << "str: " << str << std::endl;	// �Ծ��� hello, ������Ϊ������str�´�����̵߳��ڲ��洢�ռ䣬Ȼ���ڴ�洢�����ݴ���������
}
#endif

void start_thread_with_param_2()
{
    std::string str = "hello";

    std::thread t(do_some_work_by_param, std::ref(str));
    t.join();

    std::cout << "str: " << str << std::endl;	// do_some_work_by_param
}

namespace
{
class BigData
{
public:
    static const int BIG_DATA_LEN = 1024;
    void SetData(const char *data, int len)
    {
        if (len > 0 && len < BIG_DATA_LEN)
        {
            memcpy(m_data, data, len);
            m_data_len = len;
        }
    }

    int GetDataLen() const
    {
        return m_data_len;
    }
private:
    int m_data_len = 0;
    char m_data[BIG_DATA_LEN] {};
};

void process_big_data(std::unique_ptr<BigData> p_big_data)
{
    std::cout << "BigData len: " << p_big_data->GetDataLen() << std::endl; // 3
}
}

void start_thread_with_param_3()
{
    std::unique_ptr<BigData> p_big_data(new BigData());
    p_big_data->SetData("wow", sizeof("wow"));
    std::thread t(process_big_data, std::move(p_big_data));
    t.join();
    assert(nullptr == p_big_data);
}

namespace
{
class Foo
{
public:
    void do_some_work(int v)
    {
        std::cout << "Foo::do_some_work, v: " << v  << std::endl;
    }
};
}

void start_thread_by_obj_func()
{
    Foo f;
    std::thread t(&Foo::do_some_work, &f, 42);
    t.join();
}
