//
// Created by Aaron on 2019/7/27.
//

#ifndef __COPPERCOIN_SNIFFER_H__
#define __COPPERCOIN_SNIFFER_H__

typedef struct s_protocol
{
    int     tcp;
    int     udp;
    int     icmp;
    int     igmp;
    int     others;
    int     total;
} t_protocol;

typedef struct s_sniffer
{
    FILE        *logfile;
    t_protocol  *proto;
} t_sniffer;

void ProcessPacket(unsigned char*, int, t_sniffer *);
void print_ip_header(unsigned char*, int, t_sniffer *);
void print_tcp_packet(unsigned char*, int, t_sniffer *);
void print_udp_packet(unsigned char*, int, t_sniffer *);
void print_icmp_packet(unsigned char*, int, t_sniffer *);
void PrintData(unsigned char*, int, t_sniffer *);
void display_time_add_date();
void getting_started();
void signal_white_now(int);

#endif //__COPPERCOIN_SNIFFER_H__
