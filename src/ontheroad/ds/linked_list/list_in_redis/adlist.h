#ifndef __ADLIST_H__
#define __ADLIST_H__

// 双向链表
typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct listIter
{
    listNode *next;
    int direction;
} listIter;

typedef struct list
{
    listNode *head;
    listNode *tail;
    // 函数指针
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
    unsigned long len;
} list;

#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l, m) ((l)->dup = (m))
#define listSetFreeMethod(l, m) ((l)->free = (m))
#define listSetMatchMethod(l, m) ((l)->match = (m))

#define listGetDupMethod(l) ((l)->dup)
#define listGetFree(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

// prototypes
list *listCreate(void);
void listRelease(list *list);
void listEmpty(list *list);

list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *oldNode, void *value, int after);
void listDelNode(list *list, listNode *node);

listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);

void listReleaseIterator(listIter *iter);
list *listDup(list *origin);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);

void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);
void listRotate(list *list);
void listJoin(list *l, list *o);

// directions for iterators
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif