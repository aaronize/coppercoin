#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_NUM 5

char *messages[THREADS_NUM];

struct thread_data 
{
    int     thread_id;
    int     sum;
    char    *message;
};

struct thread_data thread_data_list[THREADS_NUM];

void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
    struct thread_data *my_data;

    _sleep(1);
    my_data = (struct thread_data *)threadarg;
    taskid = my_data->thread_id;
    sum = my_data->sum;
    hello_msg = my_data->message;
    printf("Thread %d: %s   Sum=%d\n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t   threads[THREADS_NUM];
    int *taskids[THREADS_NUM];
    int rc, t, sum;

    sum = 0;
    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le Monde!";
    messages[2] = "Latin: Orbis, te saluto!";
    messages[3] = "German: Guten Tag, Welt!";
    messages[4] = "Chinese: Nihao, shijie!";

    for (t = 0; t < THREADS_NUM; t++)
    {
        sum = sum + t;
        thread_data_list[t].thread_id = t;
        thread_data_list[t].sum = sum;
        thread_data_list[t].message = messages[t];

        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_list[t]);

        if (rc)
        {
            printf("ERROR, return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}

