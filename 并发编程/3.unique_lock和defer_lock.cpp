#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex a;

//std::lock_guard���ܹ�ʹ��std::defer_lock, std::unique_lock�������,���������������ϻ����һЩ

void foo1()
{
    std::unique_lock<std::mutex> lk(a, std::defer_lock);
	//std::defer_lock��std::adopt_lock�෴,���Ƕ���,����std::defer_lock�ṩ�ȹ���,��ʱ������
    //������ǰ���� 
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
    std::thread t1([] { foo1(); });//��lambda�����߳�,��lambda���ú��� 
    std::thread t2([] { foo2(); });

    t1.join(), t2.join();
}
