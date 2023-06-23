#include <iostream>

template<typename T>
struct Base {
    void foo() {
        std::cout << "Base\n";
        static_cast<T *>(this)->foo();
    }
};

struct test1 : Base<test1> {
    void foo() {
        std::cout << "test1\n";
    }
};

struct test2 : Base<test2> {
    void foo() {
        std::cout << "test2\n";
    }
};

template<typename T>
void foo(Base<T> &a) {
    a.foo();
}

int main() {
    test1 A;
    test2 B;
    A.foo();
    B.foo();
    foo(A);
    foo(B);
}
