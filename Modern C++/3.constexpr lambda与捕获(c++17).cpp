#include <iostream>

class A
{
public: 
    A() = default;
    void test()
    {
        auto foo = [*this]()mutable //*this�����ǰѵ�ǰ�Ķ��󿽱�һ�ݶ���������(*this������ҪC++17��)
        {
            a = 1;
            std::cout << a << " " << b << " " << c << std::endl;
        };
        foo();
        std::cout << a << std::endl;//a����Ϊ0�����仯
    }
private:
    int a{}, b{}, c{};
};

#include <array>

int main()
{
    auto foo1 = [] { return 5 * 3; };
    std::array<int, foo1()> a{};
    //�Ϸ�,��Ϊ��c++17��,ֻҪ���ڱ�������ֵ��lambda��������constexpr

    auto g = [](int x)constexpr -> int//��ʽ����
    {
        return x * 5;
    };

    std::cout << g(2);
}
