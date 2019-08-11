/*
1. 当控制中端退出的时候，首先会发一个挂断信号(SIGHUP)给会话首进程，一般会话首进程都是shell进程，而此动作将导致shell进程退出。
2. 当会话首进程退出时，挂断信号（SIGHUP）还会继续发送给前台进程组的所有进程。
3. 若进程未对挂断信号（SIGHUP）进行处理时，内核默认动作是终止该进程。

nohup命令让程序忽略所有的挂断信号（SIGHUP）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

// SIGHUP挂断信号处理函数
static void sig_hup_process(int signo)
{
    printf("received sighup: %d\n", signo);
    // exit(0);
}

int main(void)
{
    int count = 0;
    printf("Process started...\n");

    // 注册挂断信号
    signal(SIGHUP, sig_hup_process);
    while (1)
    {
        printf("Check -> %d\n", count++);
        sleep(1);
    }
    
    return 0;
}

