#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <vector>

void print(const std::vector<std::vector<int> >& data) {
    if (data.size() == 0) {
        return;
    }
    int start_x = 0;
    int start_y = 0;
    
    int end_x = data.size() - 1;
    int end_y = data[0].size() - 1;

    while (end_x >= start_x && end_y >= start_y) {
        // std::cout << "AB" << std::endl;
        for (int j = start_y; j < end_y; ++j) {
            std::cout << data[start_x][j] << " " << std::endl;;
        }

        // std::cout << "BC" << std::endl;
        for (int i = start_x; i < end_x; ++i) {
            std::cout << data[i][end_y] << " " << std::endl;
        }

        // std::cout << "CD" << std::endl;
        for (int j = end_y; j > start_y; j--) {
            std::cout << data[end_x][j] << " " << std::endl;
        }

        // std::cout << "DA" << std::endl;
        for (int i = end_x; i > start_x; i--) {
            std::cout << data[i][start_y] << " " << std::endl;
        }
        ++start_x;
        ++start_y;
        --end_x;
        --end_y;
    }
}

int main()
{
    std::vector<std::vector<int> > data = {
                                          {1,  2, 3, 4, 5},
                                          {10, 9, 8, 7, 6}
                                         };
    print(data);
    return 0;
}
