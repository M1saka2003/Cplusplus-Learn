#include <iostream>

//constinit 用来检查变量是否为静态变量,其次，constinit要求变量具有常量初始化程序;

constinit int a = 10;//OK

int main()
{
    //constinit int b=10;非静态
    constinit static int c = 10;//OK

    int x = 1, y = 1;

    //constinit static int d = x; x非常量

    constinit static int d = [](int a, int b)consteval { return a + b; }(1, 2);//OK
    constinit static int e = [](int a, int b) constexpr { return a + b; }(1, 2);//OK
    // constinit static int f = [](int a, int b) constexpr { return a + b; }(x, y);//非常量
}
