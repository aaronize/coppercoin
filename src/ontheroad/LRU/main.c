#include <stdio.h>
#include <string.h>

#include "lru_cache.h"
#include "lru_cache_impl.h"

int main(int argc, char **argv)
{
    void *LruCache;

    if (0 == LRUCacheCreate(3, &LruCache))
    {
        printf("缓存器创建成功，容量3");
    }

    // 创建缓存器
    printf("hello world");
    LRUCachePrint(LruCache);

    return 0;
}
