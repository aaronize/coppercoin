// http://blog.lucode.net/linux/epoll-tutorial.html
// https://www.cnblogs.com/Anker/p/3263780.html

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/types.h>

#define IP_ADDRESS  "127.0.0.1"
#define PORT        8129
#define MAX_SIZE    1024
#define LISTEN_Q    5
#define FD_SIZE     1000
#define EPOLL_EVENT 100

// 创建套接字并绑定
static int socket_bind(const char* ip, int port);
// IO多路复用epoll
static void do_epoll(int listenfd);
// 事件处理函数
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf);
// 处理接收到的连接
static void handle_accept(int epollfd, int listenfd);
// 读处理
static void do_read(int epollfd, int fd, char *buf);
// 写处理
static void do_wirte(int epollfd, int fd, char *buf);
// 添加事件
static void add_event(int epollfd, int fd, int state);
// 修改事件
static void modify_event(int epollfd, int fd, int state);
// 删除事件
static void delete_event(int epollfd, int fd, int state);


int main(int argc, char *argv[])
{
    int listenfd;
    listenfd = socket_bind(IP_ADDRESS, PORT);
    listen(listenfd, LISTEN_Q);
    do_epoll(listenfd);

    return 0;
}
