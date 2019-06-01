#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/wait.h>

#define SOCK_PATH "/tmp/echo.sock"
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s message\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCK_PATH);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect error");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE + 1];
    int nbuf;

    nbuf = strlen(argv[1]);
    send(sockfd, argv[1], nbuf, 0);
    nbuf = recv(sockfd, buf, BUF_SIZE, 0);
    buf[nbuf] = 0;
    printf("echo message: \"%s\"\n", buf);

    close(sockfd);
    return 0;
}
