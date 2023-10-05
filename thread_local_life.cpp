#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <unistd.h>
#include <vector>


void f() {
    thread_local auto i = std::make_shared<int>();
    std::cout << i << std::endl;
}
int test_cnt = 100;
void threadB()
{
    int i = 0;
    while (true)
    {
        std::cout << "B set_value: " << i << std::endl;
        if (i == (test_cnt - 1)) {
            break;
        }
        ++i;
    }
}

void threadA()
{
    int cnt = 0;
    while (true)
    {
       ++cnt;
       if (cnt == test_cnt) {
           break;
       }
    }
}

int main()
{
    std::thread tB(threadB);
    std::thread tA(threadA);
    tA.join();
    tB.join();

    return 0;
}
