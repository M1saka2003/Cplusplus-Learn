#include <iostream>

struct B {};

namespace A {
    struct B {};
    void foo(B) {
        std::cout << "foo()\n";
    }
}

int main() {
    ::B x;
    foo(x);
    A::B y;
    foo(y);
}