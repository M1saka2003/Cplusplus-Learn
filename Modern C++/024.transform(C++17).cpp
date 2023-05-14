#include <iostream>
#include <algorithm>
#include <vector>
#include <format>

int main() {
    //template< class InputIt, class OutputIt, class UnaryOperation >
    //constexpr OutputIt transform( InputIt first1, InputIt last1,OutputIt d_first, UnaryOperation unary_op );
    //
    //std::transform Ӧ�ø����ĺ�����ĳ����Χ��������洢��ʼ�� d_first ����һ��Χ

    std::vector<int> a{ 1, 2, 3 };
    std::vector<int> b;
    std::transform(a.begin(), a.end(), a.begin(), [](int x) { return x * x; });
    for (auto i : a) std::cout << std::format("{} ", i);//1 4 9
    endl(std::cout);
    std::transform(a.begin(), a.end(), std::back_inserter(b), [](int x) { return x * x; });
    //��������뵽b

    for (auto i : b) std::cout << std::format("{} ", i);//1 16 81

    std::vector<std::string> c{ "abc", "askjd", "UIASKDjkas" };

    std::transform(c.begin(), c.end(), c.begin(), [](auto& x) {
        for (auto& i : x) i = std::toupper(i);
        return x;
        });

    for (auto i : c)std::cout << std::format("{}\n", i);

}