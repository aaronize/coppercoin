/**
 * ping tool
 * 
 * IP/ICMP
 * pack/unpack
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ICMP_SIZE       (sizeof(struct icmp))
#define ICMP_ECHO       0
#define ICMP_ECHO_REPLY 0
#define BUF_SIZE        1024
#define SEND_TIEMS      5    // send datagram times

#define UCHAR   unsigned char
#define USHORT  unsigned short
#define UINT    unsigned int

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    } while (0)

// ICMP datagram structure
struct icmp
{
    UCHAR           type;       // 类型 1 byte
    UCHAR           code;       // 代码 1 byte
    USHORT          checksum;   // 校验和 2byte

    USHORT          id;         // 标识符 2 byte
    USHORT          sequence;   // 序号 2 byte

    struct timeval  timestamp;  // 时间戳 8 byte
};

// IP
struct ip
{
    // 主机字节序判断
    #if __BYTE_ORDER__ == __LITTLE_ENDIAN
    UCHAR       hlen:4;     // 首部长度
    UCHAR       version:4;  // 版本
    #endif
    #if __BYTE_ORDER__ == __BIG_ENDIAN
    UCHAR       version:4;
    UCHAR       hlen:4;
    #endif
    UCHAR       tos;        // 服务类型 1 byte
    USHORT      len;        // 总长 2 byte

    USHORT      id;         // 标识符 2 byte
    USHORT      offset;     // 标志和片偏移 2 byte

    UCHAR       ttl;        // 生存时间 1 byte
    UCHAR       protocol;   // 协议 1 byte
    USHORT      checksum;   // 校验和 2 byte

    struct in_addr  ipsrc;  // 32位源地址 4 byte

    struct in_addr  ipdst;  // 32位目的地址 4 byte
};

char buf[BUF_SIZE] = {0};

// 计算校验和
USHORT checkSum(USHORT *, int);
// 计算时间差
float timeDelta(struct timeval *, struct timeval *);
// 封装ICMP报文
void pack(struct icmp *, int);
// 对接收到的IP报文进行解包
int unpack(char *, int, char *);


int main(int argc, char *argv[])
{
    struct hostent *host;
    struct icmp sendIcmp;
    struct sockaddr_in fromAddr;
    struct sockaddr_in toAddr;
    int fromAddrLen = 0;
    int sockfd;
    int nsend = 0;
    int nreceived = 0;

    int i, n;
    in_addr_t inAddr;

    memset(&fromAddr, 0, sizeof(struct sockaddr_in));
    memset(&toAddr, 0, sizeof(struct sockaddr_in));

    if (argc < 2)
    {
        // ERR_EXIT("Use: ");
        printf("Usage: %s hostname/IP address\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 生存原始套接字
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    {
        ERR_EXIT("socket error\n");
    }

    // 设置目的地址信息
    toAddr.sin_family = AF_INET;
    // 判断是域名还是ip地址
    if (inAddr = inet_addr(argv[1]) == INADDR_NONE)
    {
        // 域名
        if ((host = gethostbyname(argv[1])) == NULL)
        {
            ERR_EXIT("get host by name error\n");
        }
        toAddr.sin_addr = *(struct in_addr *)host->h_addr_list[0];
    }
    else
    {
        toAddr.sin_addr.s_addr = inAddr;
    }

    // 输出域名/ip地址信息
    printf("PING %s (%s): %d bytes of data.\n", argv[1], inet_ntoa(toAddr.sin_addr), (int)ICMP_SIZE);

    // 循环发送报文/接收报文
    for (i = 0; i < SEND_TIEMS; i++)
    {
        nsend++;
        memset(&sendIcmp, 0, sizeof(ICMP_SIZE));
        // pack
        pack(&sendIcmp, nsend);

        // 发送报文
        if (sendto(sockfd, &sendIcmp, ICMP_SIZE, 0, (struct sockaddr *)&toAddr, sizeof(toAddr)) == -1)
        {
            printf("sendto error \n");
            continue;
        }

        // 接收报文
        if ((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&fromAddr, &fromAddrLen)) < 0)
        {
            printf("recvfrom error \n");
            continue;
        }

        nreceived++;
        if (unpack(buf, n, inet_ntoa(fromAddr.sin_addr)) == -1)
            printf("unpack error \n");

        sleep(1);
    }

    printf("--- %s ping statistics ---\n", argv[1]);
    printf("%d packets transmitted, %d received. %%%d packet loss\n", nsend, nreceived,
            (nsend - nreceived) / nsend * 100);

    return 0;
}

// icmp 
void pack(struct icmp *icmp, int sequence)
{
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->id = getpid();
    icmp->sequence = sequence;
    // gettimeofday(&icmp->timestamp, 0);
    gettimeofday(&icmp->timestamp, NULL);
    icmp->checksum = checkSum((USHORT *)icmp, ICMP_SIZE);

    return;
}

int unpack(char *buf, int len, char *addr)
{
    int i, ipHeadLen;
    struct ip *ip;
    struct icmp *icmp;
    float rtt;
    struct timeval endTime;

    ip = (struct ip *)buf;

    ipHeadLen = ip->hlen << 2;
    icmp = (struct icmp *)(buf + ipHeadLen);

    len -= ipHeadLen;

    if (len < 8)
    {
        // ERR_EXIT("ICMP packet's length is less than 8\n");
        printf("ICMP packet's length is less than 8\n");
        return -1;
    }

    if (icmp->type != ICMP_ECHO_REPLY || icmp->id != getpid())
    {
        printf("ICMP packet is valid \n");
        return -1;
    }

    gettimeofday(&endTime, 0);
    rtt = timeDelta(&icmp->timestamp, &endTime);

    printf("%d bytes from %s : icmp_seq=%u ttl=%d rtt=%fms \n", len, addr, icmp->sequence, ip->ttl, rtt);

    return 0;
}

float timeDelta(struct timeval *begin, struct timeval *end)
{
    int n;
    n = (end->tv_sec - begin->tv_sec) * 1000000 + (end->tv_usec - begin->tv_usec);

    // convert to ms
    return (float)(n / 1000);
}

// 计算校验和
USHORT checkSum(USHORT *addr, int len)
{
    UINT sum = 0;
    while (len > 1)
    {
        sum += *addr++;
        len -= 2;
    }

    if (len = 1)
    {
        sum += *(UCHAR *)addr;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (USHORT) ~sum;
}
