#include <iostream>
#include <array>

//constexpr Ҫ������ǳ������ʽ,�����ڱ�������ֵ
int main()
{
    constexpr int a1 = 10;//OK
    const int a2 = 10;//OK

    int x;

    std::array<int, a1> b1{};//OK
    std::array<int, a2> b2{};//OK
    //std::array<int,x> b3{};//�ǳ���
}
