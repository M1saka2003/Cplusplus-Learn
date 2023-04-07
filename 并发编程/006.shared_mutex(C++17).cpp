#include <thread>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;

int a = 1;
std::shared_mutex m;//C++17提供了读写锁来解决读者-写者问题

void reader()
{
    std::shared_lock<std::shared_mutex> lk(m);//RAII 读者 std::shared_lock(C++14)
    std::cout << a << "\nreader thread_id= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1ms);
}

void writer()
{
    std::unique_lock<std::shared_mutex> lk(m);//RAII 写者
    ++a;
    std::cout << "writer thread_id= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1ms);
}

int main()
{
    std::vector<std::jthread> demo;
    for (int i = 1; i <= 100; i++)
    {
        if (i % 3 == 0) demo.emplace_back(writer);
        else demo.emplace_back(reader);
    }
}
