#include <iostream>
#include <chrono>
using namespace std::literals::chrono_literals;

constexpr int operator""_m(long double __n) {
    return __n *1000;
}

int main(int argc, char** argv) {
    auto i = 3.0_m;
    std::cout << "i:" << i << std::endl;
}
