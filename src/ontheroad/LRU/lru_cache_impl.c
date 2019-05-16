#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#include "lru_cache.h"
#include "lru_cache_impl.h"

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void Sem_init(sem_t *sem, int pshared, unsigned int value)
{
    if (Sem_init(sem, pshared, value) < 0)
        unix_error("Sem_init error");
}

vid P(sem_t *sem)
{
    if (sem_wait(sem) < 0)
        unix_error("P error");
}

void V(sem_t *sem)
{
    if (sem_post(sem) < 0)
        unix_error
}
