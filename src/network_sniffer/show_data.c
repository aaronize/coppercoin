//
// Created by Aaron on 2019/7/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if _WIN32
#include <winsock.h>
#elif __linux__
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#endif

#include "sniffer.h"
#include "tools.h"

void print_ip_header(unsigned char *buf, int size, t_sniffer *sniffer)
{
    unsigned short iphdrlen;
    struct iphdr *iph;
    struct sockaddr_in src_addr;
    struct sockaddr_in dest_addr;

    iph = (struct iphdr *)buf;
    iphdrlen = iph->ihl * 4;
    (void)iphdrlen;
    (void)size;
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.sin_addr.s_addr = iph->saddr;
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_addr.s_addr = iph->daddr;

    fprintf(sniffer->logfile, "\n");
    fprintf(sniffer->logfile, "IP Header\n");
    fprintf(sniffer->logfile, "     |-IP Version        : %d\n", (unsigned int) iph->version);
    fprintf(sniffer->logfile, "     |-IP Header Length  : %d DWORDS or %d Bytes\n", (unsigned int)iph->ihl, ((unsigned int)(iph->ihl)) * 4);
    fprintf(sniffer->logfile, "     |-Type of Service   : %d\n", (unsigned int)iph->tos);
    fprintf(sniffer->logfile, "     |-IP Total Lenght   : %d Bytes(size of Packet)\n", ntohs(iph->tot_len));
    fprintf(sniffer->logfile, "     |-Identification    : %d\n",ntohs(iph->id));
	fprintf(sniffer->logfile, "     |-TTL               : %d\n",(unsigned int)iph->ttl);
	fprintf(sniffer->logfile, "     |-Protocol          : %d\n",(unsigned int)iph->protocol);
	fprintf(sniffer->logfile, "     |-Checksum          : %d\n",ntohs(iph->check));
	fprintf(sniffer->logfile, "     |-Source IP        : %s\n",inet_ntoa(src_addr.sin_addr));
	fprintf(sniffer->logfile, "     |-Destination IP   : %s\n",inet_ntoa(dest_addr.sin_addr));
}

// TODO：写 TCP 数据包到日志文件
void print_tcp_packet(unsigned char *buf, int size, t_sniffer *sniffer)
{

}

// TODO

void PrintData(unsigned char *buf, int size, t_sniffer *sniffer)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (i % 16 == 0)
            fprintf(sniffer->logfile, "\n");
        
        fprintf(sniffer->logfile, " %02X", (unsigned int)buf[i]);

        if (i == size -1)
            fprintf(sniffer->logfile, "\n");
    }
}
