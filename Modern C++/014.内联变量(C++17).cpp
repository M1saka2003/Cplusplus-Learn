#include <iostream>

struct Mystruct {
    inline static std::string msg{"OK"};//OK (��c++17��)
};

struct Mystruct1 {
//    static int a = 1; //C++�����������ʼ���ǳ�����̬��Ա
//    const static int a = 10;OK
};
//
//����һ�ζ���ԭ�� (ODR)��һ��������ʵ��Ķ���ֻ�ܳ�����һ�����뵥Ԫ�ڡ������Ǹñ�����ʵ�屻����
//Ϊinline�ġ�

struct Mystruct3 {
    static int a;
};

int Mystruct3::a = 10;//��������cpp�ļ������ᵼ������ERROR,Υ��ODR����

//Ԥ������:
#ifndef MY_HEAD
#define MY_HEAD

class Mystruct4 {
    static int a;
};

int Mystruct4 = 10;//��������CPP����,Ԥ������Ҳû��,��ΪԤ�����������ⲿ�����ݲ����ظ�����
//��������ڶ��CPP�ļ����ֵĻ�������ʱ�ᷢ��ERROR

#endif

struct Mystruct5 {
    constexpr static int a = 0;//C++11/C++14:����
    //C++17��:����
    //�ȼ�:
    //constexpr inline static int a = 0;
};
int main() {
    //�Ծ�̬��Աʹ��inline���η���,��ʹ�����cpp�ļ�����,Ҳֻ����һ��ȫ�ֶ���
}
