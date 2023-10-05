#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {
    auto page_size = getpagesize();
    std::cout << "page_size: " << page_size << std::endl;
}
