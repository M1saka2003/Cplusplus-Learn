#include <iostream>

int main()
{ 
    int x = 1, y = 1;

    //lambda实现借助仿函数也就是operator(),如下

    auto foo1 = [=](int z) {
        std::cout << x << " " << y << " " << z << std::endl;
    };

    //foo1实现等价如下

    class foo1_
    {

    public:
        foo1_(int _x, int _y) : x(_x), y(_y) {}
        void operator()(int z) const//const修饰,可以保证成员不被修改也就是值捕获,如果lambda加了mutable修饰,那么此处就没有const
        {
            std::cout << x << " " << y << " " << z << std::endl;
        }

    private:
        int x, y;
        //捕获到的参数,如果为引用捕获此处为int &x,&y;
    };

    foo1(3);//输出1 1 3
    //等价如下
    foo1_{x, y}(3);//输出1 1 3
}
