#include <iostream>
#include <condition_variable>
#include <mutex>

bool foo_flag, main_flag;
std::condition_variable cv;
std::mutex m;

using namespace std::chrono_literals;

void foo()
{
    std::cout << __func__ << " OK1\n";
    std::unique_lock<std::mutex> lk(m);

    //等待main
    cv.wait(lk, [] { return main_flag; });//当返回值为false,cv将释放锁,并且在此行阻塞.while()是为了处理虚拟唤醒
    //当被其它线程唤醒时重新获得锁

//    while (!main_flag)
//    {
//        cv.wait(lk);
//    }防止虚拟唤醒的手段

    std::cout << __func__ << " OK2\n";
    foo_flag = true;
    std::this_thread::sleep_for(1s);
    lk.unlock();//防止线程一唤醒就被阻塞
    cv.notify_one();//唤醒一个线程
}

int main()
{

    std::thread t(foo);
    std::this_thread::sleep_for(1s);
    std::cout << __func__ << " OK1\n";

    {
        std::unique_lock<std::mutex> lk(m);
        std::cout << __func__ << " OK2\n" << std::endl;
        main_flag = true;
    }

    cv.notify_one();

    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return foo_flag; });//等待foo
    }

    std::cout << __func__ << " OK3\n";
    t.join();
}
