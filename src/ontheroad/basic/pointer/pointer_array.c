#include <stdio.h>

#define SIZE 4

// 计算数组和
int sum(int *arr, int len);
// 利用指针给数组排序
int sort(int *arr, int len);

int main(void)
{
    short dates[SIZE];

    printf("%10p\n", dates);
    printf("%10p\n", &dates[0]);

    int arr[SIZE] = {1, 2, 3, 4};
    printf("sum: %d\n", sum(arr, SIZE));

    return 0;
}

int sum(int *arr, int len)
{
    int sum, i;

    for(sum = 0, i = 0; i < len; i++)
        sum += *(arr + i);
    return sum;
}
