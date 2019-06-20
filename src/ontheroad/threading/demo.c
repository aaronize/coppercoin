// https://hanbingyan.github.io/2016/03/07/pthread_on_linux/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_NUM 5

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello world! This is thread No.%d\n", tid);
    pthread_exit(NULL);

    return;
}

int main(int argc, char *argv[])
{
    pthread_t threads[THREADS_NUM];
    int rc;
    long t;

    for (t = 0; t < THREADS_NUM; t++)
    {
        printf("In main: creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc)
        {
            printf("ERROR, returncode of pthread_create %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}
