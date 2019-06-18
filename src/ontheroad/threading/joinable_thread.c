#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>

#define THREADS_NUM 5

void *BusyWork(void *t)
{
    int i;
    long tid;
    double result = 0.0;

    tid = (long)t;
    printf("Thread %ld starting...\n", tid);

    for (i = 0; i < 1000000; i++)
    {
        result = result + sin(i) * tan(i);
    }
    printf("Thread %ld done. Result = %e\n", tid, result);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread[THREADS_NUM];
    pthread_attr_t  attr;

    int rc;
    long t;
    void *status;

    // Initialize and set thread detached attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < THREADS_NUM; t++)
    {
        printf("Main: Creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
        if (rc)
        {
            printf("ERROR, return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);

    for (t = 0; t < THREADS_NUM; t++)
    {
        rc = pthread_join(thread[t], &status);
        if (rc)
        {
            printf("ERROR, return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: Completed join with thread %ld having a status of %ld\n", t, (long)status);
    }
    printf("Main: Program Completed. Exiting.\n");
    pthread_exit(NULL);
    return 0;
}
