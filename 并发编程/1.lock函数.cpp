#include <iostream>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

std::mutex a, b;

void foo()
{
    std::lock(a, b);//ͬʱ��ס����������,Ҫôͬʱ�ɹ�,���ֻ�ɹ�������һ��,��ô������ɹ���
    //���������ɹ�Ϊֹ
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
