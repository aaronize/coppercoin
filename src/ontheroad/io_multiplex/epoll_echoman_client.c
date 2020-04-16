#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SIZE    1024
#define IP_ADDRESS  "127.0.0.1"
#define PORT        8787
#define FD_SIZE     1024
#define EPOLL_EVENTS 20

static void handle_connection(int sockFd);
static void handle_events(int epollFd, struct epoll_event *events, int nfds, int sockFd, char *buf);
static void do_read(int epollFd, int fd, int sockFd, char *buf);
static void do_write(int epollFd, int fd, int sockFd, char *buf);
static void add_event(int epollFd, int fd, int type);
static void del_event(int epollFd, int fd, int type);
static void mod_event(int epollFd, int fd, int type);

int main(int argc, char *argv[])
{
    int sockFd;
    struct sockaddr_in srvaddr;
    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP_ADDRESS, &srvaddr.sin_addr);

    connect(sockFd, (struct sockaddr*)&srvaddr, sizeof(srvaddr));

    // 处理连接
    handle_connection(sockFd);
    close(sockFd);

    return 0;
}

static void handle_connection(int sockFd)
{
    int epollFd;
    struct epoll_event events[EPOLL_EVENTS];
    char buf[MAX_SIZE];

    int nfds;

    epollFd = epoll_create(FD_SIZE);

    add_event(epollFd, STDIN_FILENO, EPOLLIN);

    for (;;)
    {
        nfds = epoll_wait(epollFd, events, nfds, sockFd, buf);
        handle_events(epollFd, events, nfds, sockFd, buf);
    }
    close(epollFd);
}

static void handle_events(int epollFd, struct epoll_event *events, int nfds, int sockFd, char *buf)
{
    int fd;
    int i;
    for (i = 0; i < nfds; i++)
    {
        fd = events[i].data.fd;
        if (events[i].events & EPOLLIN)
            do_read(epollFd, fd, sockFd, buf);
        else if (events[i].events & EPOLLOUT)
            do_write(epollFd, fd, sockFd, buf);
    }
}

static void do_read(int epollFd, int fd, int sockFd, char *buf)
{
    int count;
    count = read(fd, buf, MAX_SIZE);
    if (count == -1)
    {
        perror("read error:");
        close(fd);
    }
    else if (count == 0)
    {
        fprintf(stderr, "server close.\n");
        close(fd);
    }
    else
    {
        if (fd == STDIN_FILENO)
            add_event(epollFd, sockfd, EPOLLOUT);
        else
        {
            del_event(epollFd, sockfd, EPOLLIN);
            add_event(epollFd, STDOUT_FILENO, EPOLLOUT);
        }
    }
}

static void do_write(int epollFd, int fd, int sockFd, char *buf)
{
    int count;
    count = write(fd, buf, strlen(buf));

    if (count == -1)
    {
        perror("write error:");
        close(fd);
    }
    else
    {
        if (fd == STDOUT_FILENO)
            del_event(epollFd, fd, EPOLLOUT);
        else
            mod_event(epollFd, fd, EPOLLIN);
    }
    memset(buf, 0, MAX_SIZE);
}

static void add_event(int epollFd, int sockFd, int type)
{
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = sockFd;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, sockFd, &ev);
}

static void del_event(int epollFd, int sockFd, int type)
{
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = sockFd;
    epoll_ctl(epollFd, EPOLL_CTL_DEL, sockFd, &ev);
}

static void mod_event(int epollFd, int sockFd, int type)
{
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = sockFd;
    epoll_ctl(epollFd, EPOLL_CTL_MOD, sockFd, &ev);
}
