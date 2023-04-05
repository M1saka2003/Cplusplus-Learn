#include <iostream>

int static_test1;

int main()
{
    // lambda ���ʽ�����б�ı���������һ���Զ��洢����,Ҳ���ǷǾ�̬�ľֲ�����
    //auto foo = [static_test1] {}; ����������,��Ϊstatic_test��һ��ȫ�ֱ���

    static int static_test2;

    //auto foo = [static_test2] {}; ����������,��Ϊstatic_test2��һ����̬����

    int x = 1, y = 1;

    auto foo1 = [x, y]() {};
    //auto foo1 = [x, y] { x++, y++ }; ����������,��Ϊ��ֵ���������޸�

    auto foo2 = [x, y]()mutable { ++x, ++y; };
    //std::cout << x << " " << y << std::endl;����mutable �ؼ����ܹ�ʹ��x,y�ܹ��޸ĵ������ֵ����Ϊ1,1��Ϊֵ����Ӱ��ԭ����

    auto foo3 = [&x, &y] { ++x, ++y; };//���ò���

    struct A
    {
        static void print() { std::cout << __func__ << std::endl; }
        void test()
        {
            auto foo = [this] { print(); };//this����
            //lambda ���ʽ������thisָ��,���Կ��ڱ��ʽ�ڵ��ø����͵ĳ�Ա
        }
    };

    auto foo4 = [=] {};//����lambda���ʽ�������ȫ��������ֵ
    auto f005 = [&] {};//����lambda���ʽ�������ȫ������������
}
