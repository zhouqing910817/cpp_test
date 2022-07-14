#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <atomic>

int main()
{
    std::atomic<int> a;
    a.fetch_add(1);
    std::cout << a.load() << std::endl;
    return 0;
}
