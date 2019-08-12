#include <stdio.h>
/**
 * 在C中字符串就是字节数组，并且只有不同的打印函数菜知道它们不同。
 * 
 * 注意：
 *  不能对未初始化的指针取值！
 *  因为尚未被初始化的局部指针变量并未保存一个有效的地址（是该指针所在<注：不是指向>的内存区域本来存储的值），如果尝试使用这样的指针，则将导致执行时错误。
 *  例如，
 *  int *pt; // 未初始化，该指针是一个随机值（跟其他未初始化类型类似）
 *  *pt = 5; // 这个值不值到被赋到哪块内存上了
 */
  
int main(int argc, char *argv[])
{
    int ages[] = {32, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank", "Mary", "John", "Lisa"
    };

    // sizeof返回的是占用内存大小，字节
    printf("sizeof(int) is %d.\n", sizeof(int));  // 4
    printf("sizeof(ages) is %d.\n", sizeof(ages)); // 20

    // 所以 count
    int count = sizeof(ages) / sizeof(int);

    for(int i = 0; i < count; i++)
    {
        printf("%s has %d years old.\n", names[i], ages[i]);
    }

    printf("-----------------\n");
    
    int *cur_age = ages;
    char **cur_name = names;

    for (int i = 0; i < count; i++)
    {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("++++++++++++++++++\n");
    char charvar = '\0';
    printf("address of charvar = %p\n", &charvar);
    // 和上面输出是一样的，这里加(void *)的作用是什么？
    printf("address of charvar = %p\n", (void *)(&charvar));

    return 0;
}
