#include <stdio.h>

/**
 * 在C语言中，没有专门的字符串变量类型，没有string类型，通常就用一个字符数组来存放一个字符串。
 * 
 */

int main()
{
    // C语言规定，可以将字符串直接赋值给字符数组
    char str[30] = "nihao shijie!";
    printf("output str: %s\n", str);
    // 为了方便可以不指定数组长度
    char str2[] = "nihao shijie2!";

    printf("字符串输出：%s\n", str2);

    // 字符数组只有在定义时才能将整个字符串一次性的赋值给它，一旦定义完了，就只能一个字符一个字符的赋值了
    char str3[7];
    // str = "abc123"; // 错误
    str3[0] = 'a'; str3[1] = 'b'; str3[2] = 'c';
    str3[3] = '1'; str3[4] = '2'; str3[5] = '3';
    // 注意！！字符串结束标志必须要显示赋值,否则在内存中会连后面的数据一起读出，直到读到\0字符。
    str3[6] = '\0';

    printf("string output:%s\n", str3); // 不加结束符输出：string output:abc123nihao shijie2!

    char str4[30];
    char c;
    char i;
    for (c = 65; c <= 90; c++, i++)
    {
        str4[i] = c;
    }
    str4[i] = 0;
    printf("%s\n", str4);

    return 0;
}
