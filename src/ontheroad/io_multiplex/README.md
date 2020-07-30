# I/O多路复用

> 常见的 I/O多路复用 包括：select、poll和epoll。

## select接口

```cpp
#include <sys/select.h>

// 监听多个文件socket描述符，阻塞直到有至少一个socket接收到数据
// select可以监听的文件描述符数量不能超过 FD_SETSIZE 限制，poll和epoll没有限制
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

// 取消对fd的监听
void FD_CLR(int fd, fd_set *set);
// 检查是否已监听该fd
int FD_ISSET(int fd, fd_set *set);
// 添加新的需要监听的fd
void FD_SET(int fd, fd_set *set);
// 清空所有监听的文件描述符
void FD_ZERO(fd_set *set);

int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask);
```

其中，
- maxfdp：需要监听的最大文件描述符值+1
- readfds：需要检测的可读文件描述符的集合
- writefds：可写文件描述符的集合
- excpetfds：异常文件描述符的集合


## epoll接口

```cpp
#include <sys/epoll.h>

// 创建epoll对象，返回epoll的fd。参数size是内核保证能够正确处理的最大句柄数。
// 创建epoll对象后，epoll就会占用一个fd值，使用完后必须调用close()关闭，否则可能导致fd耗尽。
int epoll_create(int size);

// epoll事件控制函数
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

