#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numbers[5] = {1, 2, 3, 4, 5};
    int numbers2[5] = {6, 7, 8, 9, 10};

    int i = 0;
    // 数组表示法取值
    for (i = 0; i < 5; i++)
    {
        int value = numbers[i];
        printf("numbers[%d] = %d\n", i, value);
    }

    // 指针输出
    int *ptr = numbers;
    for (i = 0; i < 5; i++)
    {
        int value = *ptr++;
        printf("%d, *ptr++ = %d\n", i, value);
    }

    // array type is not assignable
    // numbers = numbers2;

    // ok
    ptr = numbers2;

    return 0;
}
