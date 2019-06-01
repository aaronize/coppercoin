#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main()
{
    char fileName[100] = {0};
    printf("Input file name to save:");
    gets(fileName);
    FILE *fp = fopen(fileName, "wb");
    // TODO 
    if (fp == NULL)
    {
        printf("Cannot open file, press any key to exit!");
        fgetc(stdin);
        exit(0);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(4500);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(sockaddr));

    char buffer[BUF_SIZE] = {0};
    int nCount;
    while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0)
    {
        fwrite(buffer, nCount, 1, fp);
    }
    puts("File transfer success!");
    
    fclose(fp);
    close(sock);

    fgetc(stdin);

    return 0;
}
