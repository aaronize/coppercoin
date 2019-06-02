/**
 * extern_support.c
 * 
 */ 
#include <stdio.h>

extern int count;

void write_extern(void)
{
    printf("count is %d\n", count);
}
