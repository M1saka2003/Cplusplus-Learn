#include <iostream>

int main()
{
//    ��C++14��׼�г�����decltype��auto�����ؼ��ֵĽ���壺
//    decltype(auto)���������ü���˵�����Ǹ��߱�������
//    decltype���Ƶ����ʽ�������Ƶ�auto��������Ҫע����ǣ�
//    decltype(auto)���뵥��������Ҳ���������ܽ��ָ�롢�����Լ�
//    cv�޶�����

    int a{};
    auto x1_a = a;//int
    decltype(auto) x1_d = a;//int

    auto x2_a = (a);//int
    decltype(auto) x2_d = (a);//int &

    auto x3_a = std::move(a);//int
    decltype(auto) x3_d = std::move(a);//int&&

    auto x4_a = {1, 2};//std::initializer_list<int>
    //decltype(auto) x4_d = {1, 2};//{1,2}���Ǳ��ʽ�Ƶ�ʧ��

    auto *x5_a = &a;//int*
    //decltype(auto) *x5_d = &a;//decltype(auto) ֻ�ܵ�������,���ܼ�&����*
}


