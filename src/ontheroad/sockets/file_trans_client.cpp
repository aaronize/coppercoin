#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 1024

int main()
{
    char fileName[100] = {0};
    printf("Input filename to save:");
    gets(fileName);
    FILE *fp = fopen(fileName, "wb");
    if (fp == NULL)
    {
        printf("Cannot open file, press any key to exit!");
        system("pause");
        exit(0);
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(4500);
    connect(sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    char buffer[BUF_SIZE] = {0};
    int nCount;
    while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0)
    {
        fwrite(buffer, nCount, 1, fp);
    }
    puts("File transfer success!");

    fclose(fp);
    closesocket(sock);
    WSACleanup();
    system("pause");
    
    return 0;
}
