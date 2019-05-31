#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

#define BUF_SIZE 1024

int main()
{
    // check exist
    char fileName[] = "D:\\send.png";
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        printf("Cannont open file, press any key to exit!\n");
        system("pause");
        exit(0);
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(4500);
    bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    listen(servSock, 20);

    SOCKADDR clientAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clientSock = accept(servSock, (SOCKADDR *)&clientAddr, &nSize);

    // 
    char buffer[BUF_SIZE] = {0};
    int nCount;
    while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
    {
        send(clientSock, buffer, nCount, 0);
    }

    shutdown(clientSock, SD_SEND);
    recv(clientSock, buffer, BUF_SIZE, 0);

    fclose(fp);
    closesocket(clientSock);
    closesocket(servSock);
    WSACleanup();

    system("pause");

    return 0;
}
