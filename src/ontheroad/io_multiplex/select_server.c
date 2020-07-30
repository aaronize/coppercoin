#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#if _WIN32
#include <winsock.h>
#elif __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
    // 
#endif

#define SVR_PORT 15199
#define BACKLOG 10

#define BUF_SIZE 200

int fd_A[BACKLOG];  // accepted connection fd
int conn_amount;    // current connection amount

void showClient()
{
    int i;
    printf("Server: client amount: %d\n", conn_amount);
    for (i = 0; i < BACKLOG; i++)
    {
        printf("[%d]:%d ", i, fd_A[i]);
    }
    printf("\n\n");
}

int main(int argc, char *argv[])
{
    int sock_fd, acpt_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t sin_size;

    int yes = 1;
    char buf[BUF_SIZE];
    int ret;
    int i;

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        printf("Server: create socket error\n");
        exit(1);
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        printf("Server: set socket error\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SVR_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // 
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
    {
        printf("Server: bind port error\n");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG))
    {
        printf("Server listen error\n");
        exit(1);
    }

    printf("Server: listen port %d\n", SVR_PORT);

    // 
    fd_set fdsr;
    int maxsock;
    struct timeval tv;

    conn_amount = 0;
    sin_size = sizeof(client_addr);
    maxsock = sock_fd;
    while(1) {
        // initialize fd_set
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);

        // timeout setting
        tv.tv_sec = 30;
        tv.tv_usec = 0;

        // add active connection to fd set
        for (i = 0; i < BACKLOG; i++)
        {
            if (fd_A[i] != 0)
                FD_SET(fd_A[i], &fdsr);
        }

        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
        if (ret < 0)
        {
            printf("Server: create select error\n");
            exit(1);
        }
        else if (ret == 0)
        {
            printf("Server: create select timeout\n");
            exit(1);
        }

        // check every fd in set
        for (i = 0; i < conn_amount; i++)
        {
            if (FD_ISSET(fd_A[i], &fdsr))
            {
                ret = recv(fd_A[i], buf, sizeof(buf), 0);
                char str[] = "Good, very nice\n";

                send(fd_A[i], str, sizeof(str) + 1, 0);

                if (ret <= 0)
                {
                    printf("Server: client[%d] close\n", i);
                    close(fd_A[i]);
                    FD_CLR(fd_A[i], &fdsr);
                    fd_A[i] = 0;
                }
                else
                {
                    if (ret < BUF_SIZE)
                        memset(&buf[ret], '\n', 1);

                    printf("Server: recevie message [%s] from client[%d]\n", buf, i);
                }
                
            }
        }

        // check if there comes new connection
        if (FD_ISSET(sock_fd, &fdsr))
        {
            acpt_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &sin_size);
            if (acpt_fd < 0)
            {
                printf("Server: accept error\n");
                // exit(1);
                continue;
            }

            // add to fd queue
            if (conn_amount < BACKLOG)
            {
                fd_A[conn_amount++] = acpt_fd;
                printf("Server: new connection client[%d] %s:%d\n", conn_amount, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                if (acpt_fd > maxsock)
                    maxsock = acpt_fd;
            }
            else
            {
                printf("Server: max connection limit, exit\n");
                send(acpt_fd, "bye", 4, 0);
                close(acpt_fd);
                break;
            }
        }
        showClient();
    }

    // close other connections
    for (i = 0; i < BACKLOG; i++)
    {
        if (fd_A[i] != 0)
            close(fd_A[i]);
    }

    return 0;
}
