#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 64

typedef struct 
{
    pid_t pid;
    char buf[N];
} shm;

void handler(int signo)
{
    return;
}

int main(int argc, char **argv)
{
    key_t   key;
    int     shmid;
    shm     *p;
    pid_t   pid;

    if ((key = ftok(".", 'm') < 0))
    {
        perror("fail to ftok");
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1, handler);
    if ((shmid = shmget(key, sizeof(shm), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        if (EEXIST == errno)
        {
            shmid = shmget(key, sizeof(shm), 0666);
            p = (shm *)shmat(shmid, NULL, 0);
            pid = p->pid;
            p->pid = getpid();
            kill(pid, SIGUSR1);
        }
        else
        {
            perror("fail to shmget");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        p = (shm *)shmat(shmid, NULL, 0);
        p->pid = getpid();
        pause();
        pid = p->pid;
    }

    while (1)
    {
        pause();
        if (strcmp(p->buf, "quit\n") == 0) exit(EXIT_SUCCESS);
        printf("read from shm: %s", p->buf);
        kill(pid, SIGUSR1);
    }
    
    return 0;
}
