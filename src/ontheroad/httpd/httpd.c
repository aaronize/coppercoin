#include <stdio.h>
// Linux下
// #include <sys/socket.h>
// Windows下换成如下头文件
#include <winsock.h>
#include <sys/types.h>
// netinet.h 在Windows下包含在winsock.h下
// #include <netinet/in.h>
// Linux下
// #include <arpa/inet.h>
// Windows下换成如下
#include <Windows.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#define IsSpace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define STDIN   0
#define STDOUT  1
#define STDERR  2

void accept_request(void *);
void bad_request(int);
void cat(int, FILE *);
void cannot_execute(int);
void error_die(const char *);
void execute_cgi(int, const char *, const char *, const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
int startup(u_short *);
void unimplemented(int);


