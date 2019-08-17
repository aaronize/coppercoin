/*
具有代码块作用域的静态变量
具有文件作用域的的变量默认具有静态存储时期。
具有代码块作用域的静态变量和自动变量具有相同的作用域，但当包含这些变量的函数完成工作时，它们占用的内存并不会被释放。也就是说，这些变量具有代码块作用域、空链接，但具有静态存储时期。
当再次调用同一个函数时这个变量的值会记录上次调用后该变量的值。常用作计算器实现。
 */
#include <stdio.h>

void trystat(void);

int main(void)
{
    int count;

    printf("uninit int value: %d\n", count); // 0
    for (count = 1; count <= 3; count++)
    {
        printf("Here comes iteration %d: \n", count);
        trystat();
    }

    return 0;
}

void trystat(void)
{
    int fade = 1;
    static int stay = 1; // 第一次执行赋值，后面直接使用内存中的值
                         // 作用域只在函数代码块内部

                         // 这一句实际上并不是函数trystat()的一部分了。因为静态变量或外部变量在程序调入内存是就已经就位。

    printf("fade = %d and stay = %d\n", fade++, stay++);
}
