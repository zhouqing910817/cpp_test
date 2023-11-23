#include <string>
#include <ostream>
#include "log.h"

class People {
public:
    std::string name;
    int age;
};

std::ostream& operator<< (std::ostream& out, const People& p) {
    out << "{" << "name:" << p.name << "," << " age:" << p.age << "}";
    return out;
}

int main() {
    LOG(ERROR) << "Hello," << "world!";
    LOG(ERROR) << "Another message";

    People p = {"zhouqing", 18};
    LOG(ERROR) << p;

    LOG(INFO) << "i am INFO";
    LOG(ERROR) << "i am ERROR";
    LOG(INFO) << "i am INFO again";
    LOG(DEBUG) << "i am debug";
    LOG(WARN) << "i am warn";
    return 0;
}
