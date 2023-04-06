#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex a;

//std::try_to_lock,�᳢�Ի�ø���,���ʧ���˲�������,���Ǽ�������

void foo1()
{
    // std::lock_guard<std::mutex> lk(a, std::try_to_lock);//ֻ��unique_lock��ʹ��std::try_to_lock
    std::unique_lock<std::mutex> lk(a, std::try_to_lock);

    std::cout << __func__ << " " << "HELLO" << std::endl;

    if (lk.owns_lock())//�ж��Ƿ��õ���
    {
        std::cout << __func__ << " " << true << std::endl;
    } else
    {
        std::cout << __func__ << " " << false << std::endl;
    }
}

void foo2()
{
    std::unique_lock<std::mutex> lk(a);
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << std::endl;

}

int main()
{
    std::thread t1([] { foo1(); });
    std::thread t2([] { foo2(); });

    t1.join(), t2.join();
}
