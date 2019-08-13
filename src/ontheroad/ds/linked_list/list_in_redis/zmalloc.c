// TODO 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void zlibc_free(void *ptr)
{
    free(ptr);
}

#include <string.h>
// #include <pthread.h>
#include "zmalloc.h"
#include "atomicvar.h"

#define PREFIX_SIZE (sizeof(size_t))

#define update_zmalloc_stat_alloc(__n) do { \
    size_t _n = (__n); \
    if (_n&(sizeof(long)-1)) _n += sizeof(long) - (_n&(sizeof(long)-1)); \
    atomicIncr(used_memory, __n); \
} while(0)

void *zmalloc(size_t size)
{
    void *ptr = malloc(size + PREFIX_SIZE);

    // if (!ptr) zmalloc_oom_handler(size);

    #ifdef HAVE_MALLOC_SIZE
        update_zmalloc_stat_alloc(zmalloc_size(ptr));
        return ptr;
    #else
        *((size_t*)ptr) = size;
        update_zmalloc_stat_alloc(size + PREFIX_SIZE);
        return (char*)ptr + PREFIX_SIZE;
    #endif
}
