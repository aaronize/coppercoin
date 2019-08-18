// 测试rand0()函数
// 与rand0.c一起编译

#include <stdio.h>

extern int rand0(void);
extern void srand1(unsigned int seed);

int main(void)
{
    int count;
    unsigned seed;

    printf("Please enter your choice for seed.\n");

    while (scanf("%u", &seed) == 1)
    {
        if (seed == 0) break;
        
        srand1(seed);  // 重置种子
        for (count = 0; count < 5; count++)
            printf("%hd\n", rand0());
        printf("Please enter you choice for seed.\n");
    }
    
    printf("Done\n");
    
    return 0;
}
