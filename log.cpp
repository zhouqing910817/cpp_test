#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <memory>

class Helper {
public:
    Helper() : buffer_ptr(std::make_shared<std::stringstream>()), buffer(*buffer_ptr) {
        auto now = std::chrono::system_clock::now();
        auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(now);

        // 获取微妙部分
        auto epoch = now_us.time_since_epoch();
        auto value = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
        int microseconds = value.count() % 1000000;

        // 转换为时间_t来使用标准库
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timeInfo = std::localtime(&currentTime);

        // 输出
        buffer << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << '.' << microseconds << " ";
    }
    Helper(const Helper& h) = default;
    ~Helper() {
        if (buffer_ptr && !buffer.str().empty()) {
            std::cout << buffer.str() << std::endl;
        }
    }

    template<typename T>
    Helper& operator<<(const T& msg) {
        buffer << msg;
        return *this;
    }

private:
    std::shared_ptr<std::stringstream> buffer_ptr;
    std::stringstream& buffer;
};
class Log {
public:

    static Helper getInstance() {
        return Helper();
    }

private:
    Log() {}
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
};

#define LOG Log::getInstance()

int main() {
    LOG << "Hello, " << "world!";
    LOG << "Another message";
    return 0;
}
