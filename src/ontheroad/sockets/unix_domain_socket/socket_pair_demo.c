#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

#define BUF_SIZE 1024

/**
 * socketpair()函数用于创建一个全双工的流管道
 */
int main()
{
    signal(SIGCHLD, SIG_IGN);

    int sockfds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
    {
        perror("socket pair error");
        exit(EXIT_FAILURE);
    }

    int parent_fd = sockfds[0], child_fd = sockfds[1];

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid > 0)
    {
        close(child_fd);

        char buf[BUF_SIZE + 1] = "from parent_proc";
        int nbuf = strlen(buf);
        send(parent_fd, buf, nbuf, 0);

        nbuf = recv(parent_fd, buf, BUF_SIZE, 0);
        buf[nbuf] = 0;
        printf("parent_proc(%d) received message: %s\n", getpid(), buf);

        close(parent_fd);
    } else {
        close(parent_fd);

        char buf[BUF_SIZE + 1] = "from child_proc";
        int nbuf = strlen(buf);
        send(child_fd, buf, nbuf, 0);

        nbuf = recv(child_fd, buf, BUF_SIZE, 0);
        buf[nbuf] = 0;
        printf("child_proc(%d) received message: %s\n", getpid(), buf);

        close(child_fd);
    }

    return 0;
}
