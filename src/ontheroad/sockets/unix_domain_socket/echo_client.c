#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0) 

void echo_cli(int conn);

int main(void)
{
    int sock;
    if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
        ERR_EXIT("socket error");

    struct sockaddr_un serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "/tmp/echod.sock");

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        ERR_EXIT("connect error");
    
    echo_cli(sock);

    return 0;
}

void echo_cli(int conn)
{
    char send_buf[1024] = {0};
    char recv_buf[1024] = {0};

    while (fgets(send_buf, sizeof(send_buf), stdin) != NULL)
    {
        write(conn, send_buf, strlen(send_buf));
        read(conn, recv_buf, sizeof(recv_buf));

        fputs(recv_buf, stdout);
        memset(recv_buf, 0, sizeof(recv_buf));
        memset(send_buf, 0, sizeof(send_buf));
    }

    close(conn);
    return;
}
