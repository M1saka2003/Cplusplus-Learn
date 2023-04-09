#include <iostream>
#include <thread>
#include <mutex>
#include <random>

struct A
{
    ~A()
    {
        std::cout << "end" << std::endl;
    }
};

int main()
{
//  ��c++17��������if�������ʽ���(һ��)��ʼ�����.
    if (int x = 2;false) {}
    else if (++x > 5) {}
    else if (++x > 5) {}
    else
    {
        std::cout << x << std::endl;//OK 4
    }//����ʼ����if��䶨��ı���������if else�ж���Ч

    if (A a{};true) {}//�����end,if������ʱ����ö������������
    if (A a{};false) {}//�����end,�������ָ���ʼ������ٽ����ж�

    std::mutex m;
    if (std::lock_guard lg(m);true)
    {
        std::cout << "YES" << std::endl;
    }
    //�ȼ�����:

    {
        std::lock_guard lg(m);
        if (true)
        {
            std::cout << "YES" << std::endl;
        }
    }

    if (int x = 1, y = 2;true)//����������
    {
        std::cout << "HELLO!" << std::endl;
    }

//    if(auto x=1,y="abc";true) //�������������ͬ����

    std::pair b{1, 2};

    if (auto [x, y] = b;true)//if ����ʹ�ýṹ����
    {
        std::cout << x << " " << y << std::endl;
    }

    auto get = []() {
        std::mt19937 a{std::random_device{}()};
        return a();
    };

    if (auto k = get();k)//���ж��п���ʹ�ö���ı���
    {
        std::cout << "HELLO!" << std::endl;
    }
}

