#include <iostream>

struct Base {
    std::string a;
    int b;
};

struct derived : Base {
    int c;
};

int main() {
    derived a{{"abc", 1}, 2};//C++17��ۺ������ӵ�л���,����Ϊ�ۺϳ�ʼ��
    derived b{"abc", 1, 2};//OK

    //���û�и�����,��ʼ��������
    struct derived : Base {
        int c;
        derived(std::string a_, int b_, int c_) : Base{a_, b_}, c(c_) {}
    };

    derived c{"123", 1, 1};//OK ���ǲ��Ǿۺϳ�ʼ��ʵ�ָ��鷳

    struct Data {
        const char *p;
        double value;
    };

    struct CppData : Data {
        bool a;
    };

    CppData x{};
    CppData y{{"abc"}};//{{"abc",0.},false}
    CppData z{{}, true};//{{nullptr,0.},true}

    struct test1 {

        int a, b;
        test1(int x, int y) : a(x), b(y) {}
    };

    struct test2 : public test1 {
        int c;
    };

    test2 test{{1, 2}, 3};//�ӷǾۺ����������ۺ���

//��C++17���������������Ķ�����Ϊ�Ǿۺ���:
//1.��һ������
//2.��һ����������������������
//2.1 û���û�����ĺ�explicit�Ĺ��캯��
//2.2 û��ʹ��using�����̳еĹ��캯��
//2.3 û��private��protected�ķǾ�̬���ݳ�Ա
//2.4 û��virtual����
//2.5 û��virtual,private,protected�Ļ���
}
