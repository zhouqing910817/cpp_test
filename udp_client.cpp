#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUF 1024
#define PORT 5000
#define SERVER_IP "10.138.21.193"

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUF];

    //创建socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (1)
    {
        //获取用户输入
        fgets(buffer, MAX_BUF, stdin);

        //发送数据
        if (sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
    return 0;
}
