/*
终止处理程序：
atexit()函数用于注册终止处理函数
 */
#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void);
static void my_exit2(void);

int main(int args, char *argv[])
{
    if (atexit(my_exit2) != 0)
        printf("Cannot register my_exit2\n");
    if (atexit(my_exit1) != 0)
        printf("Cannot register my_exit1\n");

    printf("main is done\n");
    return 0;
}

static void my_exit1(void)
{
    printf("First exit handler\n");
}

static void my_exit2(void)
{
    printf("Second exit handler\n");
}
