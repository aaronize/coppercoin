#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#include "lru_cache.h"
#include "lru_cache_impl.h"

// wrappers for posix semaphores
void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void Sem_init(sem_t *sem, int pshared, unsigned int value)
{
    if (sem_init(sem, pshared, value) < 0)
        unix_error("Sem_init error");
}

void P(sem_t *sem)
{
    if (sem_wait(sem) < 0)
        unix_error("P error");
}

void V(sem_t *sem)
{
    if (sem_post(sem) < 0)
        unix_error;
}

static void freeList(LRUCacheS *cache);

// LRU缓存及缓存单元接口实现
// 创建一个缓存单元
static cacheEntryS* newCacheEntry(char *key, char *data)
{
    cacheEntryS* entry = NULL;
    if (NULL == (entry = malloc(sizeof(*entry)))) 
    {
        perror("malloc");
        return NULL;
    }
    memset(entry, 0, sizeof(*entry));
    strncpy(entry->key, key, KEY_SIZE);
    strncpy(entry->data, data, VALUE_SIZE);
    Sem_init(&(entry->entry_lock), 0, 1);

    return entry;
}

// 释放一个缓冲单元
static void freeCacheEntry(cacheEntryS* entry)
{
    if (NULL == entry) return;
    free(entry);
}

// 创建一个LRU缓存
int LRUCacheCreate(int capacity, void **lruCache)
{
    LRUCacheS* cache = NULL;
    if (NULL == (cache = malloc(sizeof(*cache))))
    {
        perror("molloc");
        return -1;
    }
    memset(cache, 0, sizeof(*cache));
    cache->cacheCapacity = capacity;
    Sem_init(&(cache->cache_lock), 0, 1);
    cache->hashMap = malloc(sizeof(cacheEntryS*)*capacity);
    if (NULL == cache->hashMap)
    {
        free(cache);
        perror("molloc");
        return -1;
    }

    memset(cache->hashMap, 0, sizeof(cacheEntryS*)*capacity);
    *lruCache = cache;
    return 0;
}

// 释放一个LRU缓存
int LRUCacheDestroy(void *lruCache)
{
    LRUCacheS* cache = (LRUCacheS*)lruCache;
    if (NULL == cache) return 0;
    if (cache->hashMap)
    {
        free(cache->hashMap);
    }

    freeList(cache);
    free(cache);
    return 0;
}

// 双向链表接口实现
// 删除指定节点
static void removeFromList(LRUCacheS *cache, cacheEntryS *entry)
{
    // 链表为空
    if (cache->lruListSize == 0)
        return;
    
    if (entry==cache->lruListHead && entry == cache->lruListTail)
    {
        // 唯一节点
        P(&cache->cache_lock);
        cache->lruListHead = entry->lruListNext;
        cache->lruListHead->lruListPrev = NULL;
        V(&cache->cache_lock);
    } 
    else if (entry == cache->lruListHead)
    {
        // 删除头结点
    }
    else if (entry == cache->lruListTail)
    {
        // 删除尾结点
    }
    else 
    {
        // 其他
    }

    // 删除成功
    P(&cache->cache_lock);
    cache->lruListSize--;
    V(&cache->cache_lock);
}

// 将结点插入到链表表头
static cacheEntryS* insertToListHead(LRUCacheS *cache, cacheEntryS *entry)
{
    cacheEntryS *removedEntry = NULL;
    P(&cache->cache_lock);
    ++cache->lruListSize;
    V(&cache->cache_lock);

    if (cache->lruListSize > cache->cacheCapacity)
    {
        removedEntry = cache->lruListTail;
        removeFromList(cache, cache->lruListTail);
    }

    if (cache->lruListHead == NULL && cache->lruListTail == NULL)
    {
        P(&cache->cache_lock);
        cache->lruListHead = cache->lruListTail = entry;
        V(&cache->cache_lock);
    } 
    else 
    {
        P(&cache->cache_lock);
        entry->lruListNext = cache->lruListHead;
        entry->lruListPrev = NULL;
        cache->lruListHead->lruListPrev = entry;
        cache->lruListHead = entry;
        V(&cache->cache_lock);
    }

    return removedEntry;
}

// 释放整个链表
static void freeList(LRUCacheS* cache)
{
    if (0 == cache->lruListSize)
    {
        return;
    }

    cacheEntryS *entry = cache->lruListHead;
    while(entry) 
    {
        cacheEntryS *temp = entry->lruListNext;
        freeCacheEntry(entry);
        entry = temp;
    }
    cache->lruListSize = 0;
}

static void updateLRUList(LRUCacheS *cache, cacheEntryS *entry)
{
    removeFromList(cache, entry);
    insertToListHead(cache, entry);
}

// TODO hash表
static unsigned int hashKey(LRUCacheS *cache, char* key)
{
    unsigned int len = strlen(key);
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;
    
    for (i = 0; i < len; key++, i++)
    {
        hash = hash * a + (unsigned int)(*key);
        a = a * b;
    }
}

// 存取接口
int LRUCacheSet(void *lruCache, char *key, char *data)
{
    LRUCacheS *cache = (LRUCacheS*)lruCache;

}
