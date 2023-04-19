#include "a.h"

template<typename T>
void A<T>::inc(T& t) {
    ++t;
}

template class A<int>;
template class A<long long>;

int main(int argc, char** argv) {
}
