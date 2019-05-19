#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int value = system("calc");
    printf("result is:%d\n", value);
    return 0;
}