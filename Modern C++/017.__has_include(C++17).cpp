#if __has_include(<iostream>)
#include <iostream>

#elif __has_include(<vector>)
#include <vector>

#endif

//C++17��չ��Ԥ����,������һ�����ĳ���ļ����Ƿ���Ա������ĺ�

int main() {

    std::cout << 1;//OK
//  std::vector<int> a;//ERROR
//  __has__include��һ�������Ԥ����ָ��,��������Դ����������ʽ

//    if (__has_include(<iostream>)){}//ERROR

}
