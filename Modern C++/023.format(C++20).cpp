#include <iostream>
#include <format>
#include <numbers>

template<typename...Args>
void print(const std::string_view str_fmt, Args &&...args) {
    std::cout << std::vformat(str_fmt, std::make_format_args(args...));
}

int main() {
    //std::format��C++20�����һ����ʽ�ַ�������
    //����ʹ��{}����ռλ��
    std::cout << std::format("Demo1 {}\n", "hello");//Demo1 hello
    std::cout << std::format("Demo2 {}+{}={}\n", 1, 2, 1 + 2);//Demo2 1+2=3
    //��{}����λ�ò����������˳��
    std::cout << std::format("Demo3 {1} {2} {0}\n", 1, 2, 3);//Demo3 2 3 1
    //ָ������
    std::cout << std::format("Demo4 {:.5}\n", std::numbers::pi);//Demo4 3.1416
    //ָ��ռ�ÿռ�
    print("Demo5 {:5}\n", 1);//Demo5     1
    //�����
    print("Demo6{:<5}\n", 1);//Demo61
    //�Ҷ���
    print("Demo7{:>5}\n", 1);//Demo7    1
    //ָ���ַ�����
    print("Demo8{:*>5}\n", 1);//Demo8****1
    //����
    print("Demo9{:^5}\n", 1);//Demo9  1
    print("Demo10{:_^5}\n", 1);//Demo10__1__
    //������
    print("Demo11 {:b}\n", 3);//Demo11 11
    //�˽���
    print("Demo12 {:o}\n", 17);//Demo12 21
    //ʮ����
    print("Demo13 {:d}\n", 012);//Demo13 10
    //ʮ������
    print("Demo14 {:x} {:X}\n", 12, 12);//Demo14 c C
}