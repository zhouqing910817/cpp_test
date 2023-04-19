#include <iostream>
#include <stdio.h>

class A {
  public:
    A() {
        std::cout << "A()" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
    void f() {
        std::cout << " f() " << std::endl;
    }
};

A a;

void after_main() __attribute__((destructor));
void after_main() {
    std::cout << "after main" << std::endl;
    a.f();
}

int main(int argc, char** argv) {
    std::cout << "in main" << std::endl;
    return 0;
}
