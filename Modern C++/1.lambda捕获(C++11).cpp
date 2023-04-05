#include <iostream>

int static_test1;

int main()
{
    // lambda ���ʽ�����б�ı���������һ���Զ��洢����,Ҳ���ǷǾ�̬�ľֲ�����
    //auto foo = [static_test1] {}; ����������,��Ϊstatic_test1��һ��ȫ�ֱ���

    static int static_test2;

    //auto foo = [static_test2] {}; ����������,��Ϊstatic_test2��һ����̬����

    int x = 1, y = 1;

    auto foo1 = [x, y]() {};//ֵ����
    //auto foo1 = [x, y] { x++, y++ }; ����������,��Ϊ��ֵ���������޸�

    auto foo2 = [x, y]()mutable { ++x, ++y; };
    //std::cout << x << " " << y << std::endl;����mutable�ؼ���ʹ��x,y�����޸ĵ�������������Ϊ1,1����Ϊֵ�����ǰ�ԭ����������һ��

    auto foo3 = [&x, &y] { ++x, ++y; };//���ò���

    struct A
    {
        static void print() { std::cout << __func__ << std::endl; }
        void test()
        {
            auto foo = [this] { print(); };//this����
            //lambda ���ʽͨ��this����ʹ�ÿ�����lambda���ʽ��ֱ�ӷ��ʳ�Ա
        }
    };

    auto foo4 = [=] {};//����lambda���ʽ�������ȫ��������ֵ
    auto foo5 = [&] {};//����lambda���ʽ�������ȫ������������

    auto foo6 = [i = 2] { std::cout << i; };

    foo6();

    auto foo7 = [&i = x] { ++i; };

    foo7();

    std::cout << x;//2
}

