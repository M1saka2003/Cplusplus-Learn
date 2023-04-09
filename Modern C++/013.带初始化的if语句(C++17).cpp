#include <iostream>
#include <thread>
#include <mutex>
#include <random>

struct A
{
    ~A()
    {
        std::cout << "end" << std::endl;
    }
};

int main()
{
//  在c++17后允许在if条件表达式添加(一条)初始化语句.
    if (int x = 2;false) {}
    else if (++x > 5) {}
    else if (++x > 5) {}
    else
    {
        std::cout << x << std::endl;//OK 4
    }//带初始化的if语句定义的变量在整个if else中都有效

    if (A a{};true) {}//会输出end,if语句结束时会调用对象的析构函数
    if (A a{};false) {}//会输出end,语句是先指向初始化语句再进行判断

    std::mutex m;
    if (std::lock_guard lg(m);true)
    {
        std::cout << "YES" << std::endl;
    }
    //等价如下:

    {
        std::lock_guard lg(m);
        if (true)
        {
            std::cout << "YES" << std::endl;
        }
    }

    if (int x = 1, y = 2;true)//定义多个变量
    {
        std::cout << "HELLO!" << std::endl;
    }

//    if(auto x=1,y="abc";true) //多个变量必须相同类型

    std::pair b{1, 2};

    if (auto [x, y] = b;true)//if 里面使用结构化绑定
    {
        std::cout << x << " " << y << std::endl;
    }

    auto get = []() {
        std::mt19937 a{std::random_device{}()};
        return a();
    };

    if (auto k = get();k)//在判断中可以使用定义的变量
    {
        std::cout << "HELLO!" << std::endl;
    }
}

