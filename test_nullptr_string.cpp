#include <iostream>
#include <stdio.h>
#include <string>

int main(int argc, char** argv) {
    char* s_p = nullptr;
    std::string str = "1";
    std::string tmp;
    tmp = s_p;
    std::cout << (str + tmp) << std::endl;
    return 0;
}
