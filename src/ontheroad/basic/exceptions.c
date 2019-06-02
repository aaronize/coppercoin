/**
 * 错误处理
 * perror() 函数显示您传给它的字符串，后跟一个冒号、一个空格和当前 errno 值的文本表示形式。
 * strerror() 函数，返回一个指针，指针指向当前 errno 值的文本表示形式。
 */ 
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main()
{
    FILE *pf;
    int errnum;
    pf = fopen("unexist.txt", "rb");
    if (pf == NULL)
    {
        errnum = errno;
        fprintf(stderr, "error code: %d\n", errno);
        perror("通过 perror 输出错误信息");
        // perror(const char *_ErrMsg); // 在表中错误输出的前面，添加自定义错误信息
        fprintf(stderr, "打开文件错误：%s\n", strerror(errnum));
        // strerror(int errno); // 通过错误码返回错误信息
    }
    else
    {
        fclose(pf);
    }
    
    return 0;
}

/**
 * 输出
 * 通过 perror 输出错误信息: No such file or directory
 * error code: 2
 * 打开文件错误：No such file or directory
 */ 
