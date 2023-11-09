#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <memory>
#include <streambuf>
#include <ostream>
#include <iostream>
#include <thread>

class LogStreamBuf : public std::streambuf {
public:
    LogStreamBuf() {
        setp(buffer, buffer + sizeof(buffer) - 1); 
    }   
    int size() {
        return int(pptr() - pbase());
    }

    int flushBuffer() {
        int len = int(pptr() - pbase());
        // std::cout << "flushBuffer len: " << len << std::endl;
        if (len <= 0) return 0;
        // 在这里处理你的日志消息，例如：
        std::cout.write(pbase(), len);
        pbump(-len);
        return len;
    }   
protected:
    virtual int_type overflow(int_type c) {
        // std::cout << "overflow c: " << (char)c << std::endl;
        if (c != EOF) {
            // std::cout << "overflow c not EOF " << std::endl;
            *pptr() = c;
            pbump(1);
        } else {
            // std::cout << "overflow c is EOF " << std::endl;
        }
        flushBuffer();
        return c;
    }   

private:
    char buffer[5];
};
class LogStream : public std::ostream {
public:
    LogStream() : std::ostream(&buf) {}

    bool empty() {
        return buf.size() <= 0;
    }
    virtual ~LogStream() {
        buf.flushBuffer();
    }
private:
    LogStreamBuf buf;
};

#define ERROR_LEVEL 0
#define WARN_LEVEL 1
#define INFO_LEVEL 2
#define DEBUG_LEVEL 3

#define RED "\033[1;31m"
#define CLEAR "\033[0m"

template<int LEVEL>
constexpr const char* level_str() {
    switch (LEVEL) {
        case ERROR_LEVEL:
            return "E";
        case INFO_LEVEL:
            return "I";
        case DEBUG_LEVEL:
            return "D";
        case WARN_LEVEL:
            return "W";
        default:
            return "unknown";
    }
}


template<int LEVEL>
constexpr const char* level_color_start() {
    if (LEVEL == ERROR_LEVEL) {
        return RED;
    }
    return "";
}

template<int LEVEL>
constexpr const char* level_color_end() {
    if (LEVEL == ERROR_LEVEL) {
        return CLEAR;
    }
    return "";
}

inline const char* get_thread_id() {
    thread_local const char* t_id_c_str = nullptr;
    thread_local std::string t_id;
    if (t_id.size() == 0) {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        t_id = std::move(ss.str());
        t_id_c_str = t_id.c_str();
    }
    return t_id_c_str;
}


template<int level>
class FormatHelper {
public:
    FormatHelper() : log_stream_ptr(std::make_shared<LogStream>()) {
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
        (*log_stream_ptr) << level_color_start<level>() << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << '.' << microseconds << " " << get_thread_id() << " " << level_str<level>() << " ";
    }
    FormatHelper(const FormatHelper& h) = default;
    ~FormatHelper() {
        // std::cout << "=====" << "~Helper()" << "====" << std::endl;
        (*log_stream_ptr) << level_color_end<level>() << "\n";
    }

    template<typename T>
    FormatHelper& operator<<(const T& msg) {
        (*log_stream_ptr) << msg;
        return *this;
    }

private:
    std::shared_ptr<LogStream> log_stream_ptr;
};
class Log {
public:

    template<int LEVEL>
    static constexpr FormatHelper<LEVEL> getInstance() {
        return FormatHelper<LEVEL>();
    }

private:
    Log() {}
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
};

#define LOG(p_level) Log::getInstance<p_level##_LEVEL>()
