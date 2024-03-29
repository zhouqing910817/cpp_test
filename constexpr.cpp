#include <iostream>
template<int LEVEL>
constexpr const char* level_str() {
    switch (LEVEL) {
        case 1:
            return "E";
        case 2:
            return "I";
        case 3:
            return "D";
        case 4:
            return "W";
        default:
            return "unknown";
    }
}


constexpr int strlen_my(const char* str) {
    if (str == nullptr) return 0;
    int index = 0;
    while(str[index++] != '\0');
    return index - 1;
}
constexpr const char* get_file_name(const char* file_path, int len)
{
    int i = len - 1;
    while (i >= 0 && file_path[i] != '/') {
        --i;
    }
    return i + 1 < len ? &file_path[i + 1] : "";
}

constexpr int add(int a, int b) {
    return a + b;
}

// c++ version should be >= c++14
int main()
{
    // static_assert(strlen_my(get_file_name(__FILE__, sizeof(__FILE__))) == 13, "get_file_name() should be evaluated at compile-time");
    // constexpr auto file_name = get_file_name(__FILE__, sizeof(__FILE__));
    // constexpr auto s_len = strlen_my(file_name);
    // static_assert(s_len == 13, "get_file_name() should be evaluated at compile-time");
    // std::cout << "file_name: " << file_name << " len: " << s_len << std::endl;
    // constexpr int a = 3;
    // constexpr int b = 5;
    // static_assert(add(a,b) == 8, "add() should be evaluated at compile-time");
    // static_assert(level_str<1>() == "E", "level_str<1>");
    constexpr const char* s = level_str<1>();
    std::cout << s << std::endl;
    return 0;
}
