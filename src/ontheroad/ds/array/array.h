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
#define arraySetFreeMethod(a, m) ((a)->free = (m))
#define arraySetMatchMethod(a, m) ((a)->match = (m))

#define arrayGetDupMethod(a) ((a)->dup)
#define arrayGetFree(a) ((a)->free)
#define arrayGetMatchMethod(a) ((a)->match)

Array* arrayCreate();
void arrayInit(Array *array, int size, int typeSize);

int arrayInsert(Array *array, size_t pos, void *const value);
size_t arraySearchValue(Array *array, void *const value);
void* arrayIndex(Array *array, size_t index);
int arrayModify(Array *array, size_t pos, void *const value);

size_t arrayLen(Array *array);
size_t arraySize(Array *array);

void arrayEmpty(Array *array);
void arrayDelValue(Array *array);
void arrayDelIndex(Array *array);

#endif
