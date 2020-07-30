#if _WIN32
#include <winsock.h>
#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const static int SERVER_PORT = 15198;
const static int MAX_PENDING = 10;
const static int MAX_RCV_BUF = 256;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage %s <port>\n", argv[0]);
        exit(1);
    }

    char buf[MAX_RCV_BUF];

    int socket_fd;
    struct sockaddr_in sa;
    int port = atoi(argv[1]);

    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd < 0) 
    {
        printf("Server: fail to create socket\n");
        exit(1);
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socket_fd, (struct sockaddr*) &sa, sizeof(sa)) < 0)
    {
        printf("failed to bind socket address\n");
        close(socket_fd);
        exit(1);
    }

    if (listen(socket_fd, MAX_PENDING) < 0)
    {
        printf("failed to listen\n");
        close(socket_fd);
        exit(1);
    }

    printf("Server: started successfully, listening on %d\n", port);
    for (;;)
    {
        struct sockaddr_in ca;

        int accepted_fd = accept(socket_fd, NULL, NULL);
        if (accepted_fd < 0)
        {
            printf("Server: failed to accept\n");
            break;
        }

        while (1)
        {
            if (read(accepted_fd, buf, MAX_RCV_BUF) < 0)
            {
                printf("Server: failed to read\n");
                break;
            }

            buf[strlen(buf)] == 0;
            printf("Server: recv from client - %s\n", buf);

            if (write(accepted_fd, buf, strlen(buf)) < 0)
            {
                printf("Server：failed to write\n");
                break;
            }

            if (strncmp(buf, "quit", 4) == 0) 
            {
                printf("done\n");
                break;
            }

        }
        close(accepted_fd);
    }

    close(socket_fd);

    return 0;
}
