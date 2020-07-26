#include <stdio.h>
#include <unistd.h>

int main()
{
    int     fd[2];  // 两个文件描述符
    pid_t   pid;

    char    buff[20];

    if (pipe(fd) < 0)
        printf("create pipe error\n");

    if ((pid = fork()) < 0) // fork子进程失败
        printf("fork error\n");
    else if (pid > 0)       // 父进程，返回的pid为子进程的进程id
    {
        close(fd[0]);       // 关闭读端
        write(fd[1], "hello my friend\n", 17);
    }
    else
    {
        close(fd[1]);   // 关闭写端
        read(fd[0], buff, 20);
        printf("%s", buff);
    }
    
    return 0;
}
