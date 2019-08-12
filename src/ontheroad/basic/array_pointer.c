#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define SPLIT_LINE (printf("\n**************************\n"))

void show_array(const double arr[], int len);
void mult_array(double arr[], int len, double mult);

int main()
{
    int numbers[5] = {1, 2, 3, 4, 5};
    int numbers2[5] = {6, 7, 8, 9, 10};

    double dip[SIZE] = {20.0, 17.66, 8.2, 15.3, 22.31};

    int i = 0;
    // 数组表示法取值
    for (i = 0; i < 5; i++)
    {
        int value = numbers[i];
        printf("numbers[%d] = %d\n", i, value);
    }
    
    SPLIT_LINE;

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
    
    SPLIT_LINE;

    printf("The original dip array: \n");
    show_array(dip, SIZE);
    mult_array(dip, SIZE, 2.5);
    printf("The dip array after calling mult_array(): \n");
    show_array(dip, SIZE);

    return 0;
}

// show array
void show_array(const double arr[], int len)
{
    int i;

    for (i = 0; i < len; i++)
        printf("%8.3f", arr[i]);
    putchar('\n');
}

void mult_array(double arr[], int len, double mult)
{
    int i;

    for (i = 0; i < len; i++)
        arr[i] *= mult;
}
