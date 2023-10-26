#include <iostream>
using namespace std;

class P {
	public:
	int i = 1;
	virtual ~P() {
		std::cout << "~P()" << std::endl;
	}
};

P getP() {
    P p;
	return p;
}
P getP2() {
    auto p = getP();
	return p;
}

void printPi(int i) {
	std::cout << "i:" <<  i << std::endl;
}
class I {
	public:
	virtual ~I() {
		auto i = getP2().i;
        std::cout << i << " a" << std::endl;
	}
};
I i;
int main()
{
	
   cout << "Hello World" << std::endl;
   return 0;
}
