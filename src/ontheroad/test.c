#include <stdio.h>
#include <string.h>

#include "./LRU/lru_cache.h"
#include "./LRU/lru_cache_impl.h"

int testVoid(void *);

int main(int argc, char **argv)
{
    void *LruCache;

    // if (0 == LRUCacheCreate(3, &LruCache))
    // {
    //     printf("缓存器创建成功，容量3");
    // }

    // // 创建缓存器
    // printf("hello world");
    // LRUCachePrint(LruCache);
    int *aval = 30;
    char *str = {0};
    int ret = testVoid(str);

    return 0;
}

int testVoid(void *a)
{

    return 0;
}
