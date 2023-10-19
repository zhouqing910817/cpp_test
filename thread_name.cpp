#include <string>
#include <pthread.h>
#include <iostream>

int main() {
    static thread_local struct InitStruct {
        InitStruct(const std::string& name)
        {
            pthread_setname_np(pthread_self(), name.substr(0, 15).c_str());
        }
    } thread_initer("main_thread");

    char threadName[16];
    pthread_getname_np(pthread_self(), threadName, sizeof(threadName));
    std::cout << "Thread name: " << threadName << std::endl;
}
