#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib") // load ws2_32.dll

int main()
{
    // initialize dll
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // create socket
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // send request to server
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(4500);
    connect(sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    // recv msg from server
    char szBuffer[MAXBYTE] = {0};
    recv(sock, szBuffer, MAXBYTE, NULL);

    // print recved msg
    printf("Message from server: %s\n", szBuffer);

    // close socket
    closesocket(sock);

    // terminate dll
    WSACleanup();

    system("pause");

    return 0;
}
