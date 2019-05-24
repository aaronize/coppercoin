#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 宏定义函数
#define ADD(x, y) x + y
#define GETMAX(a, b) ((a) > (b) ? (a):(b))

// 参数类型没法作为参数传递给函数，但是可以把参数类型传递给带参的宏
#define MALLOC(n, type) ((type*) malloc((n) *sizeof(int)))

int main()
{
    int ret = ADD(1, 2);
    printf("%d\n", ret);

    int maxNum = GETMAX(56, 39);
    printf("最大值：%d\n", maxNum);

    int *ptr = MALLOC(5, int);
    memset(ptr, 0, sizeof(*ptr));
    printf("sizeof ptr: %d\n", sizeof(*ptr));
    printf("malloc: %d\n", *ptr);

    return 0;
}
