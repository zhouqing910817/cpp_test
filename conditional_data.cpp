#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <unistd.h>
#include <vector>
template <typename T>
class ConditionalData {
private:
#define MAX_SIZE 100
public:
bool set_value(const T& t)
{
    // 发送通知给wait线程
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (data_vec.size() >= MAX_SIZE) {
            return false;
        }
        data_vec.push_back(t);
        notified = true;
    }
    cv.notify_one();
    return true;
}

bool set_value(T&& t) {
    // 发送通知给wait线程
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (data_vec.size() >= MAX_SIZE) {
            return false;
        }
        data_vec.push_back(std::move(t));
        notified = true;
    }
    cv.notify_one();
}

std::vector<T> wait() {
    // 等待set_value线程通知
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return notified; });
    notified = false;
    return std::move(data_vec);
}
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<T> data_vec;
    bool notified = false;
#undef MAX_SIZE
};
ConditionalData<int> str_cond;
int test_cnt = 1000000;
void threadB()
{
    int i = 0;
    while (true)
    {
        std::cout << "B set_value: " << i << std::endl;
        str_cond.set_value(i);
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
       auto vec = str_cond.wait();
       for (int& i : vec) {
           ++cnt;
           std::cout << "A get_value: " << i << " cnt:" << cnt << std::endl;
       }
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
