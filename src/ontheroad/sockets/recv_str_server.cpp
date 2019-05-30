#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

int main()
{
    // initialize dll
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // create socket
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // bind socket
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(4500);
    bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    // listening
    listen(servSock, 20);

    // recv client requests
    SOCKADDR clientAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clientSock = accept(servSock, (SOCKADDR *)&clientAddr, &nSize);

    // send msg to client
    char str[30] = "HelloWorld!";
    send(clientSock, str, strlen(str) + sizeof(char), NULL);

    // close socket
    closesocket(clientSock);
    closesocket(servSock);

    // terminate dll
    WSACleanup();

    return 0;
}
