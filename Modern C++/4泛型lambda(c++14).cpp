#include <iostream>

//当lambda形参列表有以auto类型是,该lambda是泛型lambda
//[](auto x, auto y) { return x + y; };
//泛型lambda(C++14起) 
//编译器为实现该lambda构造如下的代码

class lambda_
{
public:
    lambda_() = default;
    template<typename T1, typename T2>
    auto operator()(T1 x, T2 y) const
    {
        return x + y;
    }
};

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> a{1, 2, 3, 4, 5};

    //demo:
    std::for_each(a.begin(), a.end(), [](auto x) { std::cout << x * x << " "; });//1 4 9 16 25
    std::cout << std::endl;

    std::string x{"abc"}, y{"zxc"};

    auto foo = [](auto x, auto y) { return x + y; };
    std::cout << foo(x, y) << std::endl;//abczxc

    std::cout << foo(1, 2) << std::endl;//3
}
