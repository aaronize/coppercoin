#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 1024

int main()
{
    char *fileName = "/tmp/send.png";
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        printf("Cannot open file, press any key to exit!");
        fgetc(stdin); 
        exit(0);
    }

    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(4500);
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &client_addr_size);

    char buffer[BUF_SIZE] = {0};
    int nCount;
    while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
    {
        write(client_sock, buffer, nCount);
    }

    shutdown(client_sock, SHUT_WR);
    read(client_sock, buffer, BUF_SIZE);

    fclose(fp);
    close(client_sock);
    close(serv_sock);

    fgetc(stdin); 
    return 0;
}
