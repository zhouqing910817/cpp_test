#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

const char* find_char(const char* str_start, const char& c) {
    const char* ret = strchr(str_start, c);
    if (ret == NULL) {
        // just one line
        ret = strchr(str_start, '\0');
    } else {
        while (*(ret + 1) == c) {
            ++ret;
        }
    }
    return ret;
}

void parse_string(const char* str) {
    if (str == nullptr || *str == '\0') return;
    const char* line_start = str;
    const char* line_end = find_char(line_start, '\n');
    int line_index = 0;
    while (line_end != NULL) {
        // std::cout << "line_index: " << line_index << std::endl;
        const char* token_start = line_start;
        const char* token_end = find_char(token_start, ' ');

        while (token_end != NULL && token_end <= line_end) {
            int num;
            sscanf(token_start, "%d", &num);
            printf("%d ", num);
            if (*token_end == '\n' || *token_end == '\0' || *(token_end + 1) == '\0' || *(token_end + 1) == '\n') {
                printf("\n");
                if (*(token_end + 1) == '\n') {
                    ++token_end;
                }
            }
            token_start = find_char(token_end, ' ');
            token_end = find_char(token_start, ' ');
            std::cout << "next token start: " << *token_start << " end:" << *token_end << std::endl;
        }

        if (*line_end == '\0') {
            std::cout << "read end" << std::endl;
            break;
        }

        line_start = line_end + 1;
        if (*line_start == '\0') {
            return;
        }
        line_end = find_char(line_start, '\n');

        // std::cout << "next line start: " << *line_start << " end:" << *line_end << std::endl;
        ++line_index;
    }

    // const char* token_start = line_start;
    // const char* token_end = strchr(token_start, ' ');

    // while (token_end != NULL) {
    //     int num;
    //     sscanf(token_start, "%d", &num);
    //     printf("%d ", num);

    //     token_start = token_end + 1;
    //     token_end = strchr(token_start, ' ');
    // }

    // int num;
    // sscanf(token_start, "%d", &num);
    // printf("%d\n", num);
}
int main() {
    const char* str = "1 2 3 \n 4 5 6 \n 7 8 9";

    parse_string(str);

    return 0;
}

