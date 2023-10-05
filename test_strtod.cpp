#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 解析str前line_cnt行，并打印出解析后的数字
void parse_string(const char* str, int line_cnt) {
    if (line_cnt == 0) return;
    const char* line_start = str;
    const char* line_end = strchr(line_start, '\n');
    int lines = 0;
    while (line_end != NULL) {
        ++lines;
        const char* token_start = line_start;
        const char* token_end = strchr(token_start, ' ');

        while (token_end <= line_end) {
            int num;
            if(token_start[0] >= '0' and token_start[0] <= '9') {
                sscanf(token_start, "%d", &num);
                printf("%d ", num);
            }

            token_start = token_end + 1;
            token_end = strchr(token_start, ' ');
        }

        int num;
        sscanf(token_start, "%d", &num);
        printf("%d\n", num);

        line_start = line_end + 1;
        line_end = strchr(line_start, '\n');
        if (lines == line_cnt) {
            return;
        }
    }

    const char* token_start = line_start;
    const char* token_end = strchr(token_start, ' ');

    while (token_end != NULL) {
        int num;
        sscanf(token_start, "%d", &num);
        printf("%d ", num);

        token_start = token_end + 1;
        token_end = strchr(token_start, ' ');
    }

    int num;
    sscanf(token_start, "%d", &num);
    printf("%d\n", num);
}
int main() {
    const char* str = "1 2 3\n4 5 6\n7 8 9";

    parse_string(str, 1);

    return 0;
}

