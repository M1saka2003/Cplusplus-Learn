#include <functional>
#include <iostream>

//std::function������������һ������,���߷º���
//����ʹ�÷�ʽ����

void test(const std::function<void(void)> &a) {
    a();
    std::cout << std::endl;
}

void foo() {
    std::cout << __func__;
}

int main() {
    test([] { std::cout << "lambda"; });//����lambda
    test(foo);//������ͨ����
    struct A {
        void operator()() {
            std::cout << "struct";
        }
    };

    test(A{});//�洢�º���,��Ҫ���ݶ���

//    std::functionҲ���Ը�ֵ����
    std::function<void(void)> a = [] { std::cout << "111" << std::endl; };
    a();//111
    a=foo;
    a();//foo

}
