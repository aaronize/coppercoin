#include <stdio.h>

#define SIGINT 10
#define SIGHUP 11
#define SIGTERM 12

void handle_signal(int signo);
void do_while(char * message);

int main()
{
    handle_signal(10);
    do_while("try it!");

    return 0;
}

/**
 * handle_signal
 * switch语句
 * 每个分支都必须以break跳出switch语句，否则会按顺序执行后面分支（不再进行判断），直到遇到break语句为止。
 * 
 * fprintf()和printf()
 * fprintf函数似乎是异步执行的，handling ended...打印后才打印fprintf()中的内容，而printf是按顺序执行的。
 */
void handle_signal(int signo)
{
    printf("handling begin...\n");
    switch (signo)
    {
    case SIGINT:
        // fprintf(stderr, "received signal: SIGINT(%d)\n", signo);
        printf("received signal: SIGHUP(%d)\n", signo);
        break;
    case SIGHUP:
        fprintf(stderr, "received signal: SIGHUP(%d)\n", signo);
        break;
    case SIGTERM:
        fprintf(stderr, "received signal: SIGTERM(%d)\n", signo);
        break;
    default:
        fprintf(stderr, "not found signal(%d)\n", signo);
        break;
    }

    printf("handling ended...\n");
    
    return;
}

/**
 * do_while
 * 
 */
void do_while(char * message)
{
    int i = 10;
    do {
        perror(message);
        i--;
    } while (i > 0);

    return;
}
