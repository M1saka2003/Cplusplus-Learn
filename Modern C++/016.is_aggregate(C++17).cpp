#include <iostream>
#include <type_traits>//std::is_aggregate

//std::is_aggregate用来识别一个类型是否是聚合体

int main() {
    int a[]{1, 2, 3};
    std::cout << std::is_aggregate<decltype(a)>::value << std::endl;//true

    std::cout << std::is_aggregate<decltype((a))>::value << std::endl;//false

    struct test1 {
        int a, b, c;
    };

    std::cout << std::is_aggregate<test1>::value << std::endl;//true

    int x;

    std::cout << std::is_aggregate<decltype(x)>::value << std::endl;//false
}
