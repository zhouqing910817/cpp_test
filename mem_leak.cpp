#include <iostream>
#include <stdio.h>
#include <string>
#include <memory>
#include <string.h>

int main(int argc, char** argv) {
    while (true) {
        auto p = malloc(1024 * 1024 * 10);
        std::cout << p << " malloc 10m" << std::endl;
    }
    return 0;
}
