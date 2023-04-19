#include <functional>
#include <iostream>

void foo(int x) {
    std::cout << "foo(" << x << ")" << std::endl;
}

int main() {
    std::function<void(int)> f = [](int x) {
        foo(x);
    };
    if (f.target<void (*)(int)>()) {
        void (*fp)(int) = reinterpret_cast<void (*)(int)>(*(f.target<void (*)(int)>()));
        if (fp) {
            std::cout << "fp not nullptr" << std::endl;
            fp(42);
        } else {
            std::cout << "fp is nullptr" << std::endl;
        }
    } else {
        std::cout << "target is nullptr" << std::endl;
    }
    return 0;
}
