#if __has_include(<iostream>)
#include <iostream>

#elif __has_include(<vector>)
#include <vector>

#endif

//C++17扩展了预处理,增加了一个检查某个文件夹是否可以被包含的宏

int main() {

    std::cout << 1;//OK
//  std::vector<int> a;//ERROR
//  __has__include是一个纯粹的预处理指令,不能用作源码的条件表达式

//    if (__has_include(<iostream>)){}//ERROR

}
