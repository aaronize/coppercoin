#ifndef LRUCACHE_H
#define LRUCACHE_H

// 
int LRUCacheCreate(int capacity, void **lruCache);

int LRUCacheDestroy(void *lruCache);

int LRUCacheSet(void *lruCache, char *key, char *data);

char* LRUCacheGet(void *lruCache, char *key);

void LRUCachePrint(void *lruCache);

#endif