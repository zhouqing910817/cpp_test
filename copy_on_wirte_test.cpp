#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <string>

int main(int argc, char** argv) {
    std::string str1 = "abcd";
    std::string str2 = str1;
    std::cout << "str1: " << (void*)str1.data() << std::endl;
    std::cout << "str2: " << (void*)str2.data() << std::endl;
    return 0;
}
