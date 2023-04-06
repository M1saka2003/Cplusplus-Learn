#include <iostream>

int main()
{
//    在C++14标准中出现了decltype和auto两个关键字的结合体：
//    decltype(auto)。它的作用简单来说，就是告诉编译器用
//    decltype的推导表达式规则来推导auto。另外需要注意的是，
//    decltype(auto)必须单独声明，也就是它不能结合指针、引用以及
//    cv限定符。

    int a{};
    auto x1_a = a;//int
    decltype(auto) x1_d = a;//int

    auto x2_a = (a);//int
    decltype(auto) x2_d = (a);//int &

    auto x3_a = std::move(a);//int
    decltype(auto) x3_d = std::move(a);//int&&

    auto x4_a = {1, 2};//std::initializer_list<int>
    //decltype(auto) x4_d = {1, 2};//{1,2}不是表达式推导失败

    auto *x5_a = &a;//int*
    //decltype(auto) *x5_d = &a;//decltype(auto) 只能单独声明,不能加&或者*
}


