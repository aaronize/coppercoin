#include <stdlib.h>
#include <stdio.h>

#define MAX_BINDING_NUM 10

typedef struct _Object 
{
    Observer* pObserverList[MAX_BINDING_NUM];
    int number;

    void (*notify)(struct _Object* pObject);
    void (*add_observer)(Observer* pObserver);
    void (*del_observer)(Observer* pObserver);
} Object;

typedef struct _Observer
{
    Object* pObject;

    void (*update)(struct _Observer* pObserver);
} Observer;
 

void notify(struct _Object* pObject)
{
    Observer* pObserver;
    int index;

    assert(NULL != pObject);
    for (index = 0; index < pObject->number; index++)
    {
        pObserver = pObject->pObserverList[index];
        pObserver->update(pObject);
    }
}

void add_observer(Observer* pObserver)
{
    
}

void del_observer(Observer* pObserver)
{

}
