#include <iostream>
#include <vector>
//C++11
using PII = std::pair<int, int>;
typedef std::pair<int, int> pii;
//µÈ¼Û

//Alias Template

template<typename T>
using P = std::pair<T, T>;

template<typename T>
struct A {
    using Iterator = typename T::iterator;
};

int main() {
    P<int> a = {1, 2};
    std::cout << a.first << " " << a.second << std::endl;//OK 1 2
    A<std::vector<int>> b;
    std::vector<int> c{1, 2, 3};
    A<std::vector<int>>::Iterator d = c.begin();
    std::cout<<*d;//OK 1
}

