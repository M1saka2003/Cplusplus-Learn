#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex a;

//std::adopt_lock是一个结构体对象,用来标记,指当前锁已经锁住了,直接让lock_guard管理锁而不用上锁

void foo1()
{
    a.lock();
    //std::lock_gurad<std::mutex> l(a); 如果不加std::adopt_lock就会报错
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
