## 命名管道（FIFO）

1. FIFO 可以在无关的进程之间交换数据，与无名管道不同；
2. FIFO 有路径名与之相关联，它以一种特殊设备文件形式存在文件系统。

```c
#include <sys/stat.h>
int mkfifo(const char *pathname, mode_t mode);
```

其中，`mode_t mode`参数和`open`函数中的`mode`相同。

创建的FIFO文件，可以用一般的文件I/O函数来操作它。

当open一个FIFO文件时，是否设置非阻塞标志（`O_NONBLOCK`）的区别：
- 若没有指定`O_NONBLOCK`（默认），`只读open`要阻塞到某个其他进程为写而打开此FIFO文件。类似地，只写open要阻塞到某个其他进程为读而打开它；
- 若指定了`O_NONBLOCK`，则只读open立即返回。而只写将出错返回-1。如果没有进程已经为读而打开该 FIFO，其errno置ENXIO。

