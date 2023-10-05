#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <iostream>

int main() {
    // int i;
    // struct timeval tv;
    // u_int64_t sum = 0;
    // for (i = 0; i < 10000000; i++) {
    //     if (gettimeofday(&tv, NULL) == -1) {
    //         perror("gettimeofday");
    //         exit(EXIT_FAILURE);
    //     }
    //     sum += tv.tv_sec;
    // }
    // std::cout << "sum: " << sum << std::endl;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    auto start = tv.tv_usec;
    gettimeofday(&tv, NULL);
    gettimeofday(&tv, NULL);
    auto end = tv.tv_usec;
    std::cout << end - start << std::endl;
    return 0;
}
