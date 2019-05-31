#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main()
{
    char fileName[100] = {0};
    printf("Input file name to save:");
    gets(fileName);
    FILE *fp = fopen(fileName, "wb");
    // TODO 
    
}
