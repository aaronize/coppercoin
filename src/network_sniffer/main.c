//
// Created by Aaron on 2019/7/28.
//
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
// #include <sys/timeb.h>
#if _WIN32
#include <winsock.h>
#elif __linux__
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/time.h>
#endif

#include "sniffer.h"
#include "tools.h"

#define ETH_P_IP 0x0800

int exec_cmd(char *buffer, int len)
{
    if (strncmp(buffer, "quit", 4) == 0)
        return 1;
    
    return 0;
}

int command_interpreter(int sd)
{
    // TODO 
    return 0;
}


int main(int argc, char *argv[])
{
    printf("hello world!\n");

    return 0;
}
