#include <memory.h>
#include <sstream>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <vector>
int main(int argc, char** argv) {
    std::string cmd = "ls -l";
    FILE* fp = popen(cmd.c_str(), "r");
    std::stringstream ss;
    char buf[4];

    if (!fp) {
        std::cout << "popen cmd:" << cmd << " failed" << std::endl;
        return -1;
    }
    std::vector<std::string> output_vec;
    int read_buf_size = sizeof(buf) - 1;
    char* ret;
    bool line_reading = false;
    while (buf[read_buf_size - 2] = '\0', ret = fgets(buf, read_buf_size, fp), ret != 0) {
        // std::cout << "ret: " << ret << std::endl;
        char last_char = buf[read_buf_size - 2];
        // std::cout << "last char: " << int(last_char) << " '\\n':" << int('\n') << std::endl;
        if (last_char != '\0' && (last_char != '\n' && last_char != '\r')) {
            // not a line
            if (line_reading != true) {
                line_reading = true;
            }
            // std::cout << "not a line" << std::endl;
            ss << buf;
        } else {
            // is a line
            // std::cout << "a line" << std::endl;
            if (line_reading) {
                ss << buf;
                output_vec.emplace_back(std::move(std::move(ss).str()));
                ss.std::stringstream::~stringstream();
                new (&ss) std::stringstream();
                if (line_reading != false) {
                    line_reading = false;
                }
            } else {
                output_vec.emplace_back(buf);
            }
        }
    }
    std::cout << "output vec: \n";
    for (size_t i = 0; i < output_vec.size(); ++i) {
        auto& line = output_vec[i];
        std::cout << line << "*************";
    }
    std::cout << "================" << std::endl;
    return 1;
}
