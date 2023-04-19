#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <chrono>

const int size = 1024 * 1024 * 10;

uint8_t src[size] = {0};
uint8_t dst[size] = {0};

int main(int argc, char **argv) {
    memset(src, 'a', 1024);
    src[size - 1] = '\0';
    auto begin = std::chrono::high_resolution_clock::now();
	memcpy(dst, src, size);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
    // std::cout << "dst: " << dst << std::endl;
    // std::cout << "src: " << src << std::endl;
	return 0;
}
