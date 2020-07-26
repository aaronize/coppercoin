#include <stdio.h>
#include <stdlib.h>     // exite
#include <fcntl.h>      // O_WRONLY
#include <sys/stat.h>
#include <time.h>       // time

int main()
{
    int     fd;
    int     n, i;
    char    buf[1024];
    time_t  tp;

    printf("current pid: %d\n", getpid());

    // 在这之前需要首先mkfifo，并且如果没有read的话会阻塞。
    // fd和read的一样
    if ((fd = open("/tmp/fifo1", O_WRONLY)) < 0)
    {
        perror("open FIFO failed!");
        exit(1);
    }

    for (i = 0; i < 10; i++)
    {
        time(&tp);
        n = sprintf(buf, "process [%d]'s time is %s", getpid(), ctime(&tp));

        printf("send message: %s", buf);
        if (write(fd, buf, n + 1) < 0)  // 写入到FIFO文件
        {
            perror("write FIFO failed!");
            close(fd);
            exit(1);
        }
        sleep(1);
    }

    close(fd);
    return 0;
}
