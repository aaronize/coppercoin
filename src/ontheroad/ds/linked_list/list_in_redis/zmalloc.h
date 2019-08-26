
#ifndef __ZMALLOC_H__
#define __ZMALLOC_H__

#include <malloc.h>

// void * 返回不确定类型的指针
void *zmalloc(size_t size);
void zfree(void *ptr);

#endif