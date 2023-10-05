#include <iostream>
using namespace std;
inline const char* get_file_name(const char* file_path, int len) {
    int i = len - 1;                
    while(i>= 0 && file_path[i] != '/') { 
        --i;
    }                               
    return (const char*)file_path + i + 1;
}               

int main()
{
	char file_path[10] = {'1','2','/','4','5','6','7','8','9','0'};
	const char* arr2 = get_file_name(file_path, sizeof(file_path));
   cout << arr2 << std::endl;
   return 0;
}
