#include <iostream>

int main()
{
    std::pair<int, int> a{};

    auto [x1, y1]{a};//OK
    auto [x2, y2] = a;//OK
    auto [x3, y3](a);//OK

    std::cout << x1 << " " << y1 << std::endl
              << x2 << " " << y2 << std::endl
              << x3 << " " << y3 << std::endl;

    //�ṹ���󶨹�����һ�����ص���������,�ṹ����ʱ����ı�������ָ�������������ĳ�Ա

    //auto [u, v] = ms;
    //�ȼ�����:

    //auto e = ms;
    //alias name u = e.i;
    //alias name v = e.s; u,v����������ı���

    //��ʵ�����Ƕ���������İ�,�������������������ṹ���󶨵�����������ͬ.
}
