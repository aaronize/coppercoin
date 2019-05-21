#include <stdio.h>
/**
 * 在C中字符串就是字节数组，并且只有不同的打印函数菜知道它们不同。
 * 
 * 
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

    return 0;
}
