#include <iostream>

int static_test1;

int main()
{
<<<<<<< HEAD
    // lambda ���ʽ�����б�ı���������һ���Զ��洢����,Ҳ���ǷǾ�̬�ľֲ�����
    //auto foo = [static_test1] {}; ����������,��Ϊstatic_test1��һ��ȫ�ֱ���
=======
    // lambda 表达式捕获列表的变量必须是一个自动存储类型,也就是非静态的局部变量
    //auto foo = [static_test1] {}; 编译器报错,因为static_test1是一个全局变量
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066

    static int static_test2;

    //auto foo = [static_test2] {}; 编译器报错,因为static_test2是一个静态变量

    int x = 1, y = 1;

<<<<<<< HEAD
    auto foo1 = [x, y]() {};//ֵ����
    //auto foo1 = [x, y] { x++, y++ }; ����������,��Ϊ��ֵ���������޸�
=======
    auto foo1 = [x, y]() {};//值捕获
    //auto foo1 = [x, y] { x++, y++ }; 编译器报错,因为是值捕获不允许修改
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066

    auto foo2 = [x, y]()mutable { ++x, ++y; };
    //std::cout << x << " " << y << std::endl;加入mutable 关键字能够使得x,y能够修改但是输出值依旧为1,1因为值捕获不影响原变量

    auto foo3 = [&x, &y] { ++x, ++y; };//引用捕获

    struct A
    {
        static void print() { std::cout << __func__ << std::endl; }
        void test()
        {
            auto foo = [this] { print(); };//this捕获
            //lambda 表达式捕获了this指针,所以可在表达式内调用该类型的成员
        }
    };

<<<<<<< HEAD
    auto foo4 = [=] {};//����lambda���ʽ�������ȫ��������ֵ
    auto foo5 = [&] {};//����lambda���ʽ�������ȫ������������
}
=======
    auto foo4 = [=] {};//捕获lambda表达式定义域的全部变量的值
    auto foo5 = [&] {};//捕获lambda表达式定义域的全部变量的引用
}
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066
