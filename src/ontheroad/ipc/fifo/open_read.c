#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;

    // 创建成功返回0，文件已经存在则报错并返回-1
    mkfifo("/tmp/testing.fifo", 0644);

    // fd = open("/tmp/testing.fifo", O_RDONLY | O_NONBLOCK); // 非阻塞模式打开
    fd = open("/tmp/testing.fifo", O_RDONLY); // 阻塞模式打开
    if (fd == -1)
    {
        perror("open error");
        exit(EXIT_FAILURE);
        // printf("not found fifo file, creating new one...");
        // if (mkfifo("/tmp/testing.fifo", 0644) == -1)
        // {
        //     perror("create fifo error");
        //     exit(EXIT_FAILURE);
        // }
    }
    printf("read open FIFO success \n");

    char buf[128];
    while (1)
    {
        sleep(1);
        ssize_t r = read(fd, buf, sizeof(buf) - 1);
        if (r > 0)
        {
            buf[r] = '\0';
            printf("buf is: %s\n", buf);
        }
        else
        {
            perror("read error");
            return 3;
        }
    }
    
    close(fd);
    return 0;
}
