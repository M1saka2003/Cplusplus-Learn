#include <iostream>

int static_test1;

int main()
{
<<<<<<< HEAD
    // lambda 表达式捕获列表的变量必须是一个自动存储类型,也就是非静态的局部变量
    //auto foo = [static_test1] {}; 编译器报错,因为static_test1是一个全局变量
=======
    // lambda 琛ㄨ揪寮忔崟鑾峰垪琛ㄧ殑鍙橀噺蹇呴』鏄竴涓嚜鍔ㄥ瓨鍌ㄧ被鍨�,涔熷氨鏄潪闈欐�佺殑灞�閮ㄥ彉閲�
    //auto foo = [static_test1] {}; 缂栬瘧鍣ㄦ姤閿�,鍥犱负static_test1鏄竴涓叏灞�鍙橀噺
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066

    static int static_test2;

    //auto foo = [static_test2] {}; 缂栬瘧鍣ㄦ姤閿�,鍥犱负static_test2鏄竴涓潤鎬佸彉閲�

    int x = 1, y = 1;

<<<<<<< HEAD
    auto foo1 = [x, y]() {};//值捕获
    //auto foo1 = [x, y] { x++, y++ }; 编译器报错,因为是值捕获不允许修改
=======
    auto foo1 = [x, y]() {};//鍊兼崟鑾�
    //auto foo1 = [x, y] { x++, y++ }; 缂栬瘧鍣ㄦ姤閿�,鍥犱负鏄�兼崟鑾蜂笉鍏佽淇敼
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066

    auto foo2 = [x, y]()mutable { ++x, ++y; };
    //std::cout << x << " " << y << std::endl;鍔犲叆mutable 鍏抽敭瀛楄兘澶熶娇寰梮,y鑳藉淇敼浣嗘槸杈撳嚭鍊间緷鏃т负1,1鍥犱负鍊兼崟鑾蜂笉褰卞搷鍘熷彉閲�

    auto foo3 = [&x, &y] { ++x, ++y; };//寮曠敤鎹曡幏

    struct A
    {
        static void print() { std::cout << __func__ << std::endl; }
        void test()
        {
            auto foo = [this] { print(); };//this鎹曡幏
            //lambda 琛ㄨ揪寮忔崟鑾蜂簡this鎸囬拡,鎵�浠ュ彲鍦ㄨ〃杈惧紡鍐呰皟鐢ㄨ绫诲瀷鐨勬垚鍛�
        }
    };

<<<<<<< HEAD
    auto foo4 = [=] {};//捕获lambda表达式定义域的全部变量的值
    auto foo5 = [&] {};//捕获lambda表达式定义域的全部变量的引用
}
=======
    auto foo4 = [=] {};//鎹曡幏lambda琛ㄨ揪寮忓畾涔夊煙鐨勫叏閮ㄥ彉閲忕殑鍊�
    auto foo5 = [&] {};//鎹曡幏lambda琛ㄨ揪寮忓畾涔夊煙鐨勫叏閮ㄥ彉閲忕殑寮曠敤
}
>>>>>>> ad3f480e35073846fb26d3e9cb89f8a8644c2066
