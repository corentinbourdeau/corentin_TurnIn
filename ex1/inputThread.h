#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "data.c"

typedef struct BuffLock {
    pthread_mutex_t *lock;
    void *buffer;
} BuffLock;

BuffLock *makeBuffLock();
void freeBuffLock(BuffLock *bl);
void *flipEndian(void *buff, int size);
void *inputThread(void *buffer);