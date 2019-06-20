#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;

    // fd = open("/tmp/testing.fifo", O_WRONLY | O_NONBLOCK); // 非阻塞模式打开
    fd = open("/tmp/testing.fifo", O_WRONLY); // 默认阻塞模式打开
    if (fd == -1)
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }
    printf("write open FIFO success\n");

    char *msg = "hello world!\n";
    char buf[128];
    int count = 10;
    while (count--)     
    {
        ssize_t w = write(fd, msg, strlen(msg));
        sleep(1);
        if (w < 0)
        {
            perror("write error");
            return 3;
        }
    }
    close(fd);

    return 0;
}
