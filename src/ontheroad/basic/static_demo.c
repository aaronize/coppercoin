#include <stdio.h>
#include <string.h>

int func(void)
{
    // static int another_parm = 20; // 虽然存储在全局数据区，但作用域还是在代码块内部
    int count = 10;
    return count--;
}

int func_static(void)
{
    static int count = 10; // 全局数据区，编译器初始化，运行期不执行。
    return count --;
}

// 全局count和func_static函数中的静态count不冲突。
// func_static中的静态count的作用域在函数内部，但函数执行完毕后并不会被销毁释放。
int count = 1;

int main(int argc, char const *argv[])
{
    // printf("another param in func: %d\n", another_parm);
    printf("local\t\tglobal\t\tlocal_static\n");
    for (; count <= 10; ++count)
    {
        printf("%d\t\t\t%d\t\t\t%d\n", func(), count, func_static());
        // printf("---------------------------");
    }
    return 0;
}
