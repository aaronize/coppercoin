// http://blog.lucode.net/linux/epoll-tutorial.html
// https://www.cnblogs.com/Anker/p/3263780.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>

#define IP_ADDRESS      "127.0.0.1"
#define PORT            8129
#define MAX_SIZE        1024
#define LISTEN_Q        5
#define FD_SIZE         1000
#define EPOLL_EVENTS    100

// 函数声明
// 创建套接字并绑定
static int socket_bind(const char* ip, int port);
// 设置socket为非阻塞，使用ET模式时必须，LT模式时选用
static void set_nonblocking(int fd);
// IO多路复用epoll
static void do_epoll(int listenfd);
// 事件处理函数
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf);
// 处理接收到的连接
static void handle_accepted(int epollfd, int listenfd);
// 读处理
static void do_read(int epollfd, int fd, char *buf);
// 写处理
static void do_write(int epollfd, int fd, char *buf);
// 添加事件
static void add_event(int epollfd, int fd, int type);
// 修改事件
static void modify_event(int epollfd, int fd, int type);
// 删除事件
static void delete_event(int epollfd, int fd, int type);


int main(int argc, char *argv[])
{
    int listenfd;
    listenfd = socket_bind(IP_ADDRESS, PORT);
    listen(listenfd, LISTEN_Q);
    do_epoll(listenfd);

    return 0;
}

static int socket_bind(const char* ip, int port)
{
    int listenFd;
    struct sockaddr_in srvaddr;

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd == -1)
    {
        perror("socket error:");
        exit(1);
    }

    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &srvaddr.sin_addr);
    srvaddr.sin_port = htons(port);
    if (bind(listenFd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) == -1)
    {
        perror("bind error:");
        exit(1);
    }

    return listenFd;
}

static void set_nonblocking(int fd)
{
    int flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1)
        return -1;

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        return -1;
    
    return 0;
}

static void do_epoll(int listenFd)
{
    int epollFd;
    struct epoll_event events[EPOLL_EVENTS];
    int ret;
    char buf[MAX_SIZE];
    memset(buf, 0, MAX_SIZE);

    // 创建epoll文件描述符
    epollFd = epoll_create(FD_SIZE);
    // 添加监听描述符事件
    add_event(epollFd, listenFd, EPOLLIN); // 使用默认的LT

    for (;;) 
    {
        // 返回就绪的fd数量
        int nfds = epoll_wait(epollFd, events, EPOLL_EVENTS, -1);
        handle_events(epollFd, events, nfds, listenFd, buf);
    }
    close(epollFd);

    return;
}

static void add_event(int epollFd, int fd, int type)
{
    // 创建epoll事件
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = fd;
    // 添加epoll事件
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollFd, int fd, int type)
{
    // 删除epoll时间
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = fd;
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int type)
{
    // 修改监听事件
    struct epoll_event ev;
    ev.events = type;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static void handle_events(int epollFd, struct epoll_event *events, int nfds, int listenFd, char *buf)
{
    int i, fd;

    for (i = 0; i < nfds; i++)
    {
        fd = events[i].data.fd;
        if ((fd == listenFd) && (events[i].events & EPOLLIN))
            // 处理新接入的socket（accept的来自客户端的新连接请求）
           handle_accepted(epollFd, listenFd);
        else if (events[i].events & EPOLLIN)
            // 已接入的socket有数据可读
            do_read(epollFd, fd, buf);
        else if (events[i].events & EPOLLOUT)
            // 已接入的socket有数据可写
            do_write(epollFd, fd, buf);
    }
}

static void handle_accepted(int epollFd, int listenFd)
{
    struct sockaddr_in sa;
    socklen_t len = sizeof(sa);

    int infd = accept(listenFd, (struct sockaddr*)&sa, &len);
    if (infd == -1)
    {
        perror("accept error:");
        // if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        // {
        //     // 资源暂时不可读，再来一遍
        //     break;
        // }
        // else 
        // {
        //     perror("accept error:");
        //     break;
        // }
    } 
    else 
    {
        printf("accept a new client");
        // 将accept的连接fd注册到epollFd中（若epoll模式为ET，则需要设置socket为非阻塞）
        add_event(epollFd, infd, EPOLLIN);
    }
}

static void do_read(int epollFd, int fd, char *buf)
{
    int count;
    count = read(fd, buf, MAX_SIZE);

    if (count == -1)
    {
        perror("read error:");
        close(fd);
        delete_event(epollFd, fd, EPOLLIN);
    }
    else if (count == 0)
    {
        fprintf(stderr, "client close.\n");
        close(fd);
        delete_event(epollFd, fd, EPOLLIN);
    }
    else
    {
        printf("read message is: %s", buf);
        // 修改描述符对应的事件为写
        modify_event(epollFd, fd, EPOLLOUT);
    }
}

static void do_write(int epollfd, int fd, char *buf)
{
    int count;
    count = write(fd, buf, strlen(buf));

    if (count == -1)
    {
        perror("write error:");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else
        modify_event(epollfd, fd, EPOLLIN);

    memset(buf, 0, MAX_SIZE);
}
