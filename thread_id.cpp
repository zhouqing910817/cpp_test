#include <iostream>
#include <thread>
#include <sstream>

using namespace std;

std::string get_thread_id() {
    thread_local std::string t_id;
    if (t_id.size() == 0) {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        t_id = std::move(ss.str());
    }
    return t_id;
}

int main() {
    std::cout << get_thread_id() << std::endl;
    auto t = new std::thread([](){
        std::cout << get_thread_id() << std::endl;
    });
    t->join();
    delete t;
    return 0;
}
