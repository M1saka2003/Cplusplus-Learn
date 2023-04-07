#include <iostream>

template<typename...Args>
decltype(auto) left(Args &&... args)//一元左折叠
{
    return (...-args);
}

template<typename...Args>
decltype(auto) right(Args &&...args)//一元右折叠
{
    return (args-...);
}

template<typename...Args>
decltype(auto) sum(Args &&...args)
{
    //return (args+...+1*2); 编译器报错...优先级低于*
    return (args+...+(1 * 2)); //OK
}

template<typename...Args>
void print(Args &&...args)
{
    ((std::cout << args << " "), ...);
}

template<typename...Args>
void foo(Args &&...args)
{
    int a[sizeof...(args)]{(std::cout << args << std::endl, 0)...};//sizeof...获取包的大小
    for (auto i : a) std::cout << i << " ";//逗号表达式A,B,丢弃A,保留B
}
int main()
{
    int a = left(1, 2, 3);//((1-2)-3) = -4
    int b = right(1, 2, 3);//1-(2-3) = 2
    std::cout << a << " " << b << std::endl;

    std::cout << sum(1, 2, 3) << std::endl;//等价((1+2)+3)+(1*2) 而不是(1+1*2)+(2+1*2)+(3+1*2)

    print("abc", 1, 2, 3, 2 * 4);

    foo(1, 2, 3);
}
