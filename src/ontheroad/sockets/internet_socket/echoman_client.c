#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>

#if _WIN32
    #include <winsock.h>
    // #include 
#elif __linux__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

const static char* SERVER_ADDR = "127.0.0.1";
const static int MAX_BUF_SIZE = 256;

int socket_fd;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in sa;
    int res;
    int port = atoi(argv[1]);

    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd < 0) {
        perror("create socket error");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(socket_fd, (struct sockaddr*)&sa, sizeof(sa)) < 0)
    {
        perror("connection failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client: server connected successfully\n");

    char buf[MAX_BUF_SIZE];

    while(1)
    {
        fgets(buf, MAX_BUF_SIZE, stdin);
        if (strncmp(buf, "quit", 4) == 0 || strncmp(buf, "q", 1) == 0)
        {
            printf("quit\n");
            write(socket_fd, "quit", 4);
            break;
        }
        else 
        {
            printf("Client: %s\n", buf);
            int len = strlen(buf);
            if (send(socket_fd, buf, len, 0) != len)
            {
                printf("Client: send message error\n");
                break;
            }

            memset(buf, 0, MAX_BUF_SIZE);
            if (recv(socket_fd, buf, MAX_BUF_SIZE, 0) < 0)
            {
                printf("Client: failed to recevie message from server\n");
                exit(1);
            }
            printf("Client: received message - %s\n", buf);
        }
    }

    close(socket_fd);

    return 0;
}
