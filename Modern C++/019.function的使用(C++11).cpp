#include <functional>
#include <iostream>

//std::function可以用来储存一个函数,或者仿函数
//常见使用方式如下

void test(const std::function<void(void)> &a) {
    a();
    std::cout << std::endl;
}

void foo() {
    std::cout << __func__;
}

int main() {
    test([] { std::cout << "lambda"; });//储存lambda
    test(foo);//储存普通函数
    struct A {
        void operator()() {
            std::cout << "struct";
        }
    };

    test(A{});//存储仿函数,需要传递对象

//    std::function也可以赋值操作
    std::function<void(void)> a = [] { std::cout << "111" << std::endl; };
    a();//111
    a=foo;
    a();//foo

}
