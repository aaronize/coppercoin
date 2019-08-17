/*
具有外部链接的静态变量具有文件作用域、外部链接和静态存储时期。
把变量的声明放在所有函数之外，即创建了一个外部变量（默认）。
 */

#include <stdio.h>

int Errupt;
double Up[100];
extern char count;
extern void writeScreen(void);

void next(void);

int main(void)
{
    extern int Errupt;  // 可省略。链接，和上面的声明指向同一变量
    // int Errupt;      // 若不带extern则会创建一个新的自动变量，在当前作用域覆盖前面的同名声明
    extern double Up[]; // 可省略。

    printf(">>> %d\n", count);
    writeScreen();  // current count is 0
    count++;
    writeScreen(); // current count is 1 
                   // count 是静态存储时期变量，是全局的，在程序载入时已经加载就位了

    return 0;
}

void next(void)
{

}

// 会报multiple definition of `writeScreen`的错误
// void writeScreen(void)
// {
//     printf("writeScreen not in support.\n");
// }
