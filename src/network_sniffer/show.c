//
// Created by Aaron on 2019/7/27.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#include "show.h"
#include "tools.h"

void print_ip_header(unsigned char *buf, int size, t_sniffer *sniffer)
{
    unsigned short iphdrlen;
    struct iphdr *iph;
    struct sockaddr_in source;
    struct sockaddr_in dest;

    iph = (struct iphdr *)buf;
    iphdrlen = iph->ihl * 4;
    (void)iphdrlen;
    (void)size;
    memset(&source, 0, sizeof(source))
}
