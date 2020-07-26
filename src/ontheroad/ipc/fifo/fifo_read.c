#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

const char *path = "/tmp/fifo1";

int main()
{
    int     fd;
    int     len;
    char    buf[1024];

    if (mkfifo(path, 0666) < 0 && errno != EEXIST)
        perror("create FIFO failed!");
    
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        perror("open FIFO error");
        exit(1);
    }

    while ((len = read(fd, buf, 1024)) > 0)
    {
        printf("received message: %s", buf);
    }

    // while (1) {
    //     read(fd, buf, 1024);  // write端关闭后，read也不会阻塞
    //     printf("received message: %s\n", buf);
    // }
    
    close(fd);
    return 0;
}
