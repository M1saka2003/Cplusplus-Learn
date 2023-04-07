#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex a;

//std::lock_guard不能够使用std::defer_lock, std::unique_lock更加灵活,但是在性能消耗上会更大一些

void foo1()
{
    std::unique_lock<std::mutex> lk(a, std::defer_lock);
	//std::defer_lock与std::adopt_lock相反,都是对象,但是std::defer_lock提供先管理,暂时不上锁
    //不能提前上锁 
	lk.lock();
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << std::endl;
}

void foo2()
{
    std::unique_lock<std::mutex> lk(a);
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << std::endl;

}

int main()
{
    std::thread t1([] { foo1(); });//用lambda创建线程,用lambda调用函数 
    std::thread t2([] { foo2(); });

    t1.join(), t2.join();
}
