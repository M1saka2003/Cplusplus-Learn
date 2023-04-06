#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std::chrono_literals;

std::once_flag flag;

//若多个线程会调用同一个函数,但是只想要函数只生效一次,可以通过call_once和once_flag
//来控制,不过前提是必须为同一个flag,不同的flag无法达到控制目的
//若该调用抛异常，则传播异常给 call_once 的调用方，并且不翻转 flag ，以令其他调用将得到尝试

int main()
{
    std::vector<std::jthread> a;
    int cur = 1;

    for (int i = 1; i <= 100; i++)
    {
        a.emplace_back([](int &x) {

            call_once(flag, [&]() {
                std::cout << x << std::endl;
                x++;
            });
            std::cout << "end" << std::endl;//每个线程都会阻塞等待call_once执行完成
        }, std::ref(cur));
    }

    std::cout << cur << std::endl;
}
