#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std::chrono_literals;

std::once_flag flag;

//������̻߳����ͬһ������,����ֻ��Ҫ����ֻ��Чһ��,����ͨ��call_once��once_flag
//������,����ǰ���Ǳ���Ϊͬһ��flag,��ͬ��flag�޷��ﵽ����Ŀ��
//���õ������쳣���򴫲��쳣�� call_once �ĵ��÷������Ҳ���ת flag �������������ý��õ�����

int main()
{
    std::vector<std::jthread> a;
    int cur = 1;

    for (int i = 1; i <= 100; i++)
    {
        a.emplace_back([](int &x) {

            call_once(flag, [&]() {
                std::cout << x << std::endl;
                x++;
            });
            std::cout << "end" << std::endl;//ÿ���̶߳��������ȴ�call_onceִ�����
        }, std::ref(cur));
    }

    std::cout << cur << std::endl;
}
