#ifndef UTILITY_H_INCLUDE
#define UTILITY_H_INCLUDE

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

// clients_list 保存所有client sockets
list<int> clients_list;

#define SERVER_IP "127.0.0.1"

#define SERVER_PORT 8980

#define EPOLL_SIZE 5000

// message buffer size
#define BUF_SIZE 0xFFFF

#define SERVER_WELCOME "Welcome to the chat room! Your char ID is: Client #%d"

#define SERVER_MESSAGE "ClientID %d say >> %s"

#define EXIT "EXIT"

#define CAUTION "There is only one in the chat room!"

/**
 * 
 * 
 * */
int setNonBlocking(int sockfd)
{
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
    return 0;
}

void addfd(int epolldf, int fd, bool enable_et)
{
    struct epoll_event ev;
    ev.data.fd = fd;
}

#endif