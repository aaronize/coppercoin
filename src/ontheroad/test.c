#include <stdio.h>
#include <string.h>

typedef struct TestSt
{
    unsigned short      sa_family;
    char                sa_data[14];
} TestSt;

int main(int argc, char **argv)
{
    // 
    int sockfd;
    struct sockaddr_in  my_addr;
    u_short port = 8080;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        exit(1);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    // my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_addr.s_addr = inet_addr("192.168.32.128");

    // 把my_addr.sin_zero的前8个字节置零
    bzero(&(my_addr.sin_zero), 8);

    bind(sockfd, (struct sockaddr *)*my_addr, sizeof(struct sockaddr));

    return 0;
}
