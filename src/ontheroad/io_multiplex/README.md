# epoll

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

### 
