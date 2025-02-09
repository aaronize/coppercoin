#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

Array* arrayCreate()
{
    struct Array *array = NULL;
    array = malloc(sizeof(*array));

    if (NULL == array)
    {
        return NULL;
    }

    array->p = NULL;

    array->size = 0;
    array->typeSize = 0;
    array->len = 0;

    array->dup = NULL;
    array->free = NULL;
    array->match = NULL;

    return array;
}

void arrayInit(Array *array, int size, int typeSize)
{
    if (NULL == array || typeSize <= 0 || size < 0)
    {
        return;
    }

    void *p = calloc(1, size * typeSize);
    if (NULL == p)
    {
        return;
    }

    array->p = p;
    array->len = 0;
    array->size = size;
    array->typeSize = typeSize;
}

// 在pos位置插入值value
int arrayInsert(Array *array, size_t pos, void *const value)
{
    if (NULL == array || array->len >= array->size || (pos > array->size || pos <= 0))
    {
        return -1;
    }

    char *pBegin = array->p;
    for (size_t i = array->len; i > pos - 1; --i)
    {
        void *pNew = pBegin + i * array->typeSize;
        void *pOld = pBegin + (i - 1) * array->typeSize;
        if (NULL != array->dup)
        {
            array->dup(pNew, pOld);
        }
        else
        {
            memcpy(pNew, pOld, array->typeSize);
        }
    }

    void *pCopy = (void *)(pBegin + ((pos - 1) * array->typeSize));
    if (NULL != array->dup)
    {
        array->dup(pCopy, value);
    }
    else
    {
        memcpy(pCopy, value, array->typeSize);
    }

    ++array->len;
    return 0;
}
