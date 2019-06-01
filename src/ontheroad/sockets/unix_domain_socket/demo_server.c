#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define SOCK_PATH "/tmp/echo.sock"
#define BUF_SIZE 1024

int listenfd;
void handle_signal(int signo);

int main()
{
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);
    signal(SIGTERM, handle_signal);

    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    // serv_addr.sun_path = SOCK_PATH;
    strcpy(serv_addr.sun_path, SOCK_PATH);

    unlink(SOCK_PATH);
    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
    chmod(SOCK_PATH, 00640);

    if (listen(listenfd, SOMAXCONN) < 0)
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    int connfd, nbuf;
    char buf[BUF_SIZE + 1];
    for (;;)
    {
        if ((connfd = accept(listenfd, NULL, NULL)) < 0)
        {
            perror("accept error");
            continue;
        }

        nbuf = recv(connfd, buf, BUF_SIZE, 0);
        buf[nbuf] = 0;
        printf("new messaeg: \"%s\"\n", buf);
        send(connfd, buf, nbuf, 0);

        close(connfd);
    }

    return 0;
}

void handle_signal(int signo)
{
    switch (signo)
    {
    case SIGINT:
        fprintf(stderr, "received signal: SIGINT(%d)\n", signo);
        break;
    case SIGHUP:
        fprintf(stderr, "received signal: SIGHUP(%d)\n", signo);
        break;
    case SIGTERM:
        fprintf(stderr, "received signal: SIGTERM(%d)\n", signo);
        break;
    default:
        break;
    }

    close(listenfd);
    unlink(SOCK_PATH);
    exit(EXIT_SUCCESS);
}
