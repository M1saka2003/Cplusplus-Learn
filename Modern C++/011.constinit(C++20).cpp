#include <iostream>

//constinit �����������Ƿ�Ϊ��̬����,��Σ�constinitҪ��������г�����ʼ������;

constinit int a = 10;//OK

int main()
{
    //constinit int b=10;�Ǿ�̬
    constinit static int c = 10;//OK

    int x = 1, y = 1;

    //constinit static int d = x; x�ǳ���

    constinit static int d = [](int a, int b)consteval { return a + b; }(1, 2);//OK
    constinit static int e = [](int a, int b) constexpr { return a + b; }(1, 2);//OK
    // constinit static int f = [](int a, int b) constexpr { return a + b; }(x, y);//�ǳ���
}
