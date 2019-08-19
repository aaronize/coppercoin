/*
一般地，对应每个malloc()调用，应该调用一次free()。
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;

    // ptd是作为指向一个double类型值的指针声明的，而不是指向30个double类型值的数据块的指针。
    // 数组的名字是它第一个元素的地址。malloc返回分配内存块的第一个字节的地址，因此可以像数组一样使用ptd
    double *ptd;
    ptd = (double *)malloc(30 * sizeof(double));

    ptd[0] = 1;
    ptd[2] = 3;

    printf("ptd: %p\n", ptd);
    // printf("ptd[0]: %p\n", ptd[0]);
    printf("ptd[0]: %f", ptd[0]);

    // 创建一个动态数组
    ptd = (double *)malloc(n * sizeof(double));
    // C99之前不允许下面定义
    // double item[n];  // expression must have a constant value

    return 0;
}
