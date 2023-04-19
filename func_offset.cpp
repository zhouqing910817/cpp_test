#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cerrno>

long int get_func_offset(const char *binary_path, const char *func_name)
{
    char cmd[256];
    char line[256];
    char *token;
    long int offset = -1;
    FILE *fp;

    /* Construct readelf command */
    snprintf(cmd, sizeof(cmd), "readelf -s %s", binary_path);

    /* Open pipe to read readelf output */
    fp = popen(cmd, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open pipe to readelf: %s\n", strerror(errno));
        return -1;
    }

    /* Read readelf output line by line */
    while (fgets(line, sizeof(line), fp)) {
        /* Skip header line */
        if (strstr(line, "Num:") == line) {
            continue;
        }

        // printf("parse line: %s", line);
        /* Parse line */
        char cp_line[256];
        strcpy(cp_line, line);
        char* addr = NULL;
        char* type = NULL;
        for (int i = 0; i < 8; ++i) {
            if (i == 0) {
                token = strtok(line, " \t");
            } else {
                token = strtok(NULL, " \t");
            }
            if (!token) {
                break;
            }
            // printf("got %d token: %s \n", i, token);
            if (i == 1) {
                addr = token;
            }
            if (i == 3) {
                type = token;
            }
            // if (i == 7)
            //     printf("compare %s and %s \n", token, func_name);
            if (i == 7 && strstr(token, func_name) != NULL && strcmp(type, "FUNC") == 0) {
                offset = strtol(addr, NULL, 16);
                printf("got offset: %ld addr:%s line: %s \n", offset, addr, cp_line);
                // break;
            }
        }
    }

    /* Close pipe */
    pclose(fp);

    return offset;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf(" usage: ./func_offset /bin/path func_name \n");
        return 0;
    }
    long int offset = get_func_offset(argv[1], argv[2]);
    if (offset == -1) {
        fprintf(stderr, "Failed to get offset of function %s\n", argv[2]);
        return 1;
    }
    printf("Offset of function foo is 0x%lx\n", offset);
}
