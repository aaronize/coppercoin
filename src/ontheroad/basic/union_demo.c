#include <stdio.h>
#include <string.h>

union Data
{
    /* Union 共用体，允许在相同的内存位置存储不用的数据类型。但任何时候只能使用一个成员 */
    int     id;
    float   value;
    char    name[20];
    char    *ip;
};

int main()
{
    union Data data;
    data.id = 6001;
    printf("data.id: %d\n", data.id);

    data.value = 100.5;
    printf("data.value: %f\n", data.value);
    // 这个时候访问下id
    printf("data.id: %d\n", data.id); // 错误的输出 data.id: 1120468992
    
    // 超过字符数组长度。warning: '__builtin_memcpy' writing 26 bytes into a region of size 24 overflows the destination
    strcpy(data.name, "physical machine location");
    printf("data.name: %s\n", data.name);
    printf("data.name's length: %d\n", strlen(data.name));

    data.ip = "192.168.168.1";
    printf("data.ip: %s\n", data.ip);
    printf("data.ip: %c\n", data.ip[2]);

    return 0;
}
