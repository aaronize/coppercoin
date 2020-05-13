/**
 * variable-precision SWAR
 * 计算汉明重量
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long int uint32_t;

uint32_t swar(uint32_t i);

int main(int argc, char const *argv[])
{
    uint32_t case1 = 3;
    uint32_t count = swar(case1);

    printf("count: %d\n", count);
    return 0;
}

uint32_t swar(uint32_t i)
{
    i = (i & 0x55555555) + ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i & 0x0F0F0f0F) + ((i >> 4) & 0x0F0F0F0F);
    i = (i *(0x01010101) >> 24);

    return i;
}
