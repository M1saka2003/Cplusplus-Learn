#include <iostream>

int main()
{
    int a{};

    decltype(a) b = 1;//��decltype(T)����һ��δ�����ŵı�ʶ�����ʽʱ,�Ƶ���T����
    
    decltype(++a) c = a;//decltype(T)����һ����ֵ���ʽʱ�Ƶ���T&
    std::cout << a << std::endl;//0 decltype(++a) Ϊ����ֵ���ʽ

    decltype((a)) d = a;//��decltype(T)���Ǳ�ʶ����������ʱ,����Ϊ����ֵ���ʽ,�Ƶ���T&

    decltype(std::move(a)) e = 2;//�����ʽ�ڲ���һ������ֵʱ�Ƶ���T&&
    
    decltype(a++) f = a;//�����ʽ�ڲ���һ������ֵʱ�Ƶ���T
}
