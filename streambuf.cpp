#include <streambuf>
#include <ostream>
#include <iostream>

class LogStreamBuf : public std::streambuf {
public:
    LogStreamBuf() {
        setp(buffer, buffer + sizeof(buffer) - 1);
    }

protected:
    virtual int_type overflow(int_type c) {
        std::cout << "overflow c: " << (char)c << std::endl;
        if (c != EOF) {
            std::cout << "overflow c not EOF " << std::endl;
            *pptr() = c;
            pbump(1);
        } else {
            std::cout << "overflow c is EOF " << std::endl;
        }
        flushBuffer();
        return c;
    }

    int flushBuffer() {
        int len = int(pptr() - pbase());
        std::cout << "flushBuffer len: " << len << std::endl;
        if (len <= 0) return 0;
        // 在这里处理你的日志消息，例如：
        std::cout.write(pbase(), len);
        pbump(-len);
        return len;
    }

private:
    char buffer[5];
};
class LogStream : public std::ostream {
public:
    LogStream() : std::ostream(&buf) {}

private:
    LogStreamBuf buf;
};
int main() {
    LogStream log;
    log << "Hello, world!";
    return 0;
}
