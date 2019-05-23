#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct Array
{
    // 指针的空间大小
    size_t      size;
    // 已使用的空间大小
    size_t      len;
    // 数据类型大小
    size_t      typeSize;
    void(*dup)(void *ptr, void *key);
    void(*free)(void *ptr);
    int(*match)(void *ptr, void *key);

    void *p;
} Array;

#define arraySetDupMethod(a, m) ((a)->dup = (m))


#endif
