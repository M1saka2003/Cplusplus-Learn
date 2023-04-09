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

    //结构化绑定过程有一个隐藏的匿名对象,结构化绑定时引入的变量名都指向这个匿名对象的成员

    //auto [u, v] = ms;
    //等价如下:

    //auto e = ms;
    //alias name u = e.i;
    //alias name v = e.s; u,v是匿名对象的别名

    //绑定实际上是对匿名对象的绑定,匿名对象的生命周期与结构化绑定的生命周期相同.
}
