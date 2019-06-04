/**
 * 预处理区分不同平台，实现跨平台编译链接。
 */
#include <stdio.h>

#if _WIN64
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

int main()
{
    #if _WIN64
    printf("running in win64\n");
    #elif __linux__
    printf("running in linux\n");
    #endif

    return 0;
}
