#ifndef LRUCACHEIMPL_H
#define LRUCACHEIMPL_H

#include <semaphore.h>

#define KEY_SIZE 50
#define VALUE_SIZE 100

typedef struct cacheEntryS
{
    /* data */
    char key[KEY_SIZE];
    char data[VALUE_SIZE];

    sem_t entry_lock;

    struct cacheEntryS *hashListPrev;
    struct cacheEntryS *hashListNext;
    
    struct cacheEntryS *lruListPrev;
    struct cacheEntryS *lruListNext;
    
} cacheEntryS;

typedef struct LRUCacheS
{
    /* data */
    sem_t cache_lock;
    int cacheCapacity;
    int lruListSize;

    cacheEntryS **hashMap;

    cacheEntryS *lruListHead;
    cacheEntryS *lruListTail;
} LRUCacheS;

#endif