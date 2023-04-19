#include <iostream>
#include <stdio.h>
#include <fstream>

std::string add(std::string str1) {
    std::cout << str1;
    return std::string("1") + str1;
}

int main(int argc, char** argv) {
    const std::string path = "test2.txt";
    for (int i = 0; i< 200; ++i) {
        std::ifstream fileStream(path.data());
        if (!fileStream.is_open()) {
            std::cout << "open file faield, path:" << path << std::endl;
        } else {
            std::cout << "open file suc, path: " << path << std::endl;
        }
    }
    add("2");
    return 0;
}
