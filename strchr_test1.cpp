
// CPP program to find position of a character
// in a given string.
#include <iostream>
#include <cstring>
using namespace std;
 
int main()
{
    char str[] = "My name is Ayush";
    char* ch = strchr(str, '\0');
    cout << ch - str + 1 << std::endl;
    return 0;
}
