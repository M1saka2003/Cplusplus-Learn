#include <iostream>

int main()
{
    int a{};

    decltype(a) b = 1;//当decltype(T)内是一个未加括号的标识符表达式时,推导出T类型
    
    decltype(++a) c = a;//decltype(T)内是一个左值表达式时推导出T&
    std::cout << a << std::endl;//0 decltype(++a) 为不求值表达式

    decltype((a)) d = a;//当decltype(T)内是标识符加上括号时,被认为是左值表达式,推导出T&

    decltype(std::move(a)) e = 2;//当表达式内部是一个将亡值时推导出T&&
    
    decltype(a++) f = a;//当表达式内部是一个纯右值时推导出T
}
