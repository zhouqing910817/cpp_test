#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>

char* addr;
int fd = -1;
struct stat sb;

void print_content() {
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Failed to get file size, fd: " << fd << std::endl;
        close(fd);
        return;
    }
    std::cout << "size: " << sb.st_size << std::endl;
    std::string content(addr, sb.st_size);
    std::cout << content.substr(0, 20) << std::endl;
}

int main() {
    fd = open("/tmp/stat", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open /tmp/stat" << std::endl;
        return -1;
    }
    std::cout << "open fd: " << fd << std::endl;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Failed to get file size" << std::endl;
        close(fd);
        return -1;
    }
    addr = static_cast<char*>(mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (addr == MAP_FAILED) {
        std::cerr << "Failed to mmap /tmp/stat" << std::endl;
        close(fd);
        return -1;
    }
    while (true) {
        print_content();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    if (munmap(addr, sb.st_size) == -1) {
        std::cerr << "Failed to munmap /tmp/stat" << std::endl;
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
