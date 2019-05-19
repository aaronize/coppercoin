#include <stdio.h>
#include <string.h>

int func(void)
{
    int count = 10;
    return count--;
}

int func_static(void)
{
    static int count = 10; // 全局数据区，编译器初始化，运行期不执行。
    return count --;
}

int count = 1;

int main(int argc, char const *argv[])
{
    printf("local\t\tglobal\t\tlocal_static\n");
    for (; count <= 10; ++count)
    {
        printf("%d\t\t\t%d\t\t\t%d\n", func(), count, func_static());
        // printf("---------------------------");
    }
    return 0;
}
