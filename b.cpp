#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <vector>

static int a = 0;
static int b = 0;
void f()
{
    std::cout << "a: " << a << " b:" << b << std::endl;
}
