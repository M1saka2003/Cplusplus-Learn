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

    //�ȴ�main
    cv.wait(lk, [] { return main_flag; });//������ֵΪfalse,cv���ͷ���,�����ڴ�������.while()��Ϊ�˴������⻽��
    //���������̻߳���ʱ���»����

//    while (!main_flag)
//    {
//        cv.wait(lk);
//    }��ֹ���⻽�ѵ��ֶ�

    std::cout << __func__ << " OK2\n";
    foo_flag = true;
    std::this_thread::sleep_for(1s);
    lk.unlock();//��ֹ�߳�һ���Ѿͱ�����
    cv.notify_one();//����һ���߳�
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
        cv.wait(lk, [] { return foo_flag; });//�ȴ�foo
    }

    std::cout << __func__ << " OK3\n";
    t.join();
}
