#include <iostream>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

std::mutex a, b;

void foo()
{
    std::lock(a, b);//同时锁住两个互斥量,要么同时成功,如果只成功了其中一个,那么会解锁成功的
    //会阻塞到成功为止
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    a.unlock(), b.unlock();
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}
