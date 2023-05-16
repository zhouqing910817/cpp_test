#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>

int main(int argc, char** argv) {
    while (true) {
        if (argc != 2) {
            std::cout << " need 2 params" << std::endl;
            return -1;
        }
        FILE* pipe = popen(argv[1], "r");
        if (!pipe) {
            std::cerr << "popen() failed!" << std::endl;
            return 1;
        }
        char buffer[128];
        while (fgets(buffer, 128, pipe) != NULL) {
            std::cout << buffer;
        }
        pclose(pipe);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
