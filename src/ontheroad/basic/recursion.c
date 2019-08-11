#include <stdio.h>

// 递归
void up_and_down(int);

// 尾递归，递归调用出现在尾部。尾递归作用相当于一条循环语句，是最简单的一种递归形式。
// 实现阶乘
long tail_recursion_fact(int);
long for_fact(int); // 循环实现阶乘

// 反向计算
// 十进制整数转换成二进制
void to_binary(unsigned long n);

int main(void)
{
    // up_and_down(1);

    int num;

    printf("This program calculates factorials.\n");
    printf("Enter a value in the range 0-12 (q to quit): \n");
    while (scanf_s("%d", &num) == 1)
    {
        if (num < 0)
            printf("No negative numbers, please.\n");
        else if (num > 12)
            printf("Keep input under 13. \n");
        else
        {
            printf("loop: %d factorial = %ld\n", num, for_fact(num));
            printf("recursion: %d factorial = %ld\n", num, tail_recursion_fact(num));
        }
        printf("Enter a value in the range 0-12 (q to quit): \n");
    }
    printf("Bye.\n");
    return 0;
}

void up_and_down(int n)
{
    printf("Level %d: n location %p\n", n, &n);
    if (n < 4)
        up_and_down(n + 1);

    printf("LEVEL %d: n location %p\n", n, &n);
}

// 尾递归（tail recursion)或者结尾递归（end recursion）
long tail_recursion_fact(int n)
{
    long ans;

    if (n > 0)
        ans = n * tail_recursion_fact(n - 1);
    else
        ans = 1;
    
    return ans;
}
// 循环实现阶乘
long for_fact(int n)
{
    long ans;

    for (ans = 1; n > 1; n--)
        ans *= n;

    return ans;
}

// 二进制
void to_binary(unsigned long n)
{
    int r;
    r = n % 2;
    if (n >= 2)
        to_binary(n / 2);
    putchar('0' + r);

    return;
}
