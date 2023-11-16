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

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //绑定到端口
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("udp server listen on %d \n", PORT);

    while (1)
    {
        memset(buffer, 0, MAX_BUF);
        //接收数据
        if (recvfrom(sockfd, (char *)buffer, MAX_BUF, 0, (struct sockaddr *)&client_addr, &addr_len) < 0)
        {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        //打印接收到的数据
        printf("%s:%d _> %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
    }

    close(sockfd);
    return 0;
}
