#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static bool stop = false;

void signal_handler_fun(int signum) {
    std::cout << "catch signal:" << signum << std::endl;
    stop = true;
}

int main(int argc, char** argv) {
    
    std::cout << "in main" << std::endl;
    signal(SIGINT, signal_handler_fun);
    while(!stop) {
        sleep(10000);
    }
    return 0;
}
