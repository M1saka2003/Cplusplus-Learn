#include <iostream>

template<typename...Args>
decltype(auto) left(Args &&... args)//һԪ���۵�
{
    return (...-args);
}

template<typename...Args>
decltype(auto) right(Args &&...args)//һԪ���۵�
{
    return (args-...);
}

template<typename...Args>
decltype(auto) sum(Args &&...args)
{
    //return (args+...+1*2); ����������...���ȼ�����*
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
    int a[sizeof...(args)]{(std::cout << args << std::endl, 0)...};//sizeof...��ȡ���Ĵ�С
    for (auto i : a) std::cout << i << " ";//���ű��ʽA,B,����A,����B
}
int main()
{
    int a = left(1, 2, 3);//((1-2)-3) = -4
    int b = right(1, 2, 3);//1-(2-3) = 2
    std::cout << a << " " << b << std::endl;

    std::cout << sum(1, 2, 3) << std::endl;//�ȼ�((1+2)+3)+(1*2) ������(1+1*2)+(2+1*2)+(3+1*2)

    print("abc", 1, 2, 3, 2 * 4);

    foo(1, 2, 3);
}
