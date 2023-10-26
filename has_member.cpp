#include <iostream>
#include <string>
#include <type_traits>
using namespace std;
template<typename T>
struct has_member_xxxx
{
	template<typename U>
	static double check(decltype(&U::service_addr_));
 
	// 否则, 下面chech<T>(0)调用本函数
	// 返回值是int
	template<typename U>
	static int check(...);
 
	// 如果check<T>(0)的返回值是void, 
	// 则&T::xxxx合法, xxxx是T的成员
	typedef decltype(check<T>(nullptr)) type; 
	// enum { value = std::is_void<decltype(check<T>(0))>::value };
};

template<typename E>
const char* get_service_addr(double t, const E& s) {
    return s->service_addr_.c_str();
}

template<typename E>
const char* get_service_addr(int t, const E& s) {
    return s->yyyy.c_str();
}
class P {
	public:
	std::string service_addr_;
};
class S : public P{
	public:
	
	std::string yyyy = "no service address";
};

int main()
{
	S s;
	s.service_addr_ = "ark_os://fdaf";

   cout << get_service_addr(has_member_xxxx<decltype(s)>::type(0), &s) << std::endl;
   return 0;
}
