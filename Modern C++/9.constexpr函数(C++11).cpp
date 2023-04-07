#include <iostream>
#include <array>

//constexpr�������Խ�����Ϊ����ʱ�ڱ�������ֵ

template<typename...Args>
constexpr decltype(auto) foo(Args &&...args)
{
//	  C++14��
//    1. ����������������
//    2�������������if��switch��䣬����ʹ��go��䡣
//    3�������������е�ѭ����䣬����for��while��do-while��
//    4�����������޸��������ںͳ������ʽ��ͬ�Ķ���
//    5�������ķ���ֵ��������Ϊvoid��
    int sum{};
    ((sum += args), ...);
    return sum;
}
int main()
{
    std::cout << foo(1, 2, 3) << std::endl;//6 OK
    int x = 1, y = 1, z = 1;
    std::cout << foo(x, y, z) << std::endl;//�ǳ���OK,�˻�Ϊ��ͨ����

    constexpr int t1 = foo(1, 2, 3);//OK
    //constexpr int t2 = foo(x, y, z);//foo(x,y,z)�ǳ���

    std::array<int, foo(1, 2, 3)> t2{};//OK
    //std::array<int,foo(x,y,z)>t3{}; ����ǳ���
}
