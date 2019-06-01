/**
 * UNIX Domain Socket
 * Socket API原本是为网络通讯设计的，但后来在socket的框架上发展出一种IPC机制，就是UNIX Domain Socket。
 * 使用UNIX Domain Socket的过程和网络socket十分相似，也要先调用socket()创建一个socket文件描述符，
 * address family指定为AF_UNIX，type可以选择SOCK_DGRAM或SOCK_STREAM，protocol参数仍然指定为0即可。
 * 
 * #define UNIX_PATH_MAX    108
 * 
 * struct sockaddr_un {
 *    sa_family_t sun_family;        // AF_UNIX
 *    char sun_path[UNIX_PATH_MAX];  // pathname 
 * };
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)

void echo_server(int conn);

int main(void)
{
    int listend;
    if ((listend = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
        ERR_EXIT("socket error");

    unlink("/tmp/echod.sock");
    struct sockaddr_un serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "/tmp/echod.sock");

    if (bind(listend, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        ERR_EXIT("bind error");

    if (listen(listend, SOMAXCONN) < 0)
        ERR_EXIT("listen error");

    int conn;
    pid_t pid;

    while (1)
    {
        conn = accept(listend, NULL, NULL);
        if (conn == -1)
        {
            if (conn == EINTR)
                continue;
            ERR_EXIT("accept error");
        }

        pid = fork();
        if (pid < 0)
            ERR_EXIT("fork error");
        if (pid == 0)
        {
            close(listend);
            echo_server(conn);
            exit(EXIT_SUCCESS);
        }

        close(conn);
    }

    return 0;
}

void echo_server(int conn)
{
    char recv_buf[1024];
    int n;
    while (1)
    {
        memset(recv_buf, 0, sizeof(recv_buf));
        n = read(conn, recv_buf, sizeof(recv_buf));
        if (n == -1)
        {
            if (n == EINTR)
                continue;
            
            ERR_EXIT("read error");
        }
        else if (n == 0)
        {
            printf("client close\n");
            break;
        }

        fputs(recv_buf, stdout);
        write(conn, recv_buf, strlen(recv_buf));
    }

    close(conn);
}
