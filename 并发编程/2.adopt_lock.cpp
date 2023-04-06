#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex a;

//std::adopt_lock��һ���ṹ�����,�������,ָ��ǰ���Ѿ���ס��,ֱ����lock_guard����������������

void foo1()
{
    a.lock();
    //std::lock_gurad<std::mutex> l(a); �������std::adopt_lock�ͻᱨ��
    std::lock_guard<std::mutex> lk(a, std::adopt_lock);
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << std::endl;
}

void foo2()
{
    std::lock_guard<std::mutex> lk(a);
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << std::endl;
}

int main()
{
    std::thread t1(foo1);
    std::thread t2(foo2);

    t1.join();
    t2.join();
}
