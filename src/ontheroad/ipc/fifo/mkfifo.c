#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s fifoname \n", argv);
        exit(EXIT_FAILURE);
    }
    if (mkfifo(argv[1], 0644) == -1)
    {
        perror("mkfifo error");
        exit(EXIT_FAILURE);
    }
    printf("create FIFO success \n");

    return 0;
}
