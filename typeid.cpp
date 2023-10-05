#include <iostream>
#include <cstring>
#include <vector>

std::string getFunctionSymbol(const std::string& signature) {
    // 解析命名空间、类名和函数名
    size_t nsPos = signature.find("::");
    size_t clsPos = signature.find("::", nsPos + 2);
    size_t fnPos = signature.rfind("::");
    std::string nsName = signature.substr(0, nsPos);
    std::string clsName = signature.substr(nsPos + 2, clsPos - nsPos - 2);
    std::string fnName = signature.substr(fnPos + 2);
    
    // 构造函数参数类型列表
    std::vector<std::string> argList;
    size_t start = fnPos + 2;
    size_t end = signature.find_first_of(")", start + 1);
    while (start < end) {
        size_t len = end - start - 1;
        std::string argType = signature.substr(start + 1, len);
        argList.push_back(argType);
        start += len + 1;
    }
    
    // 构造函数符号
    std::string symbol = "_Z";
    symbol += std::to_string(nsName.length());
    symbol += nsName;
    symbol += std::to_string(clsName.length());
    symbol += clsName;
    symbol += std::to_string(fnName.length());
    symbol += fnName;
    for (const auto& arg : argList) {
        symbol += std::to_string(arg.length());
        symbol += arg;
    }
    return symbol;
}

int main() {
    // 示例输入
    std::string signature = "np::sub_np::classname::add(int, int)";
    
    // 获取函数符号并打印出来
    std::string symbol = getFunctionSymbol(signature);
    std::cout << "Function symbol: " << symbol << std::endl;
    
    return 0;
}
