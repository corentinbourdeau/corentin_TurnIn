#define BUFF 1024
#include "inputThread.h"

BuffLock *makeBuffLock() {
    BuffLock *result = malloc(sizeof (BuffLock));
    result->buffer = malloc(BUFF);
    result->lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(result->lock, NULL);

    return result;
}

void freeBuffLock(BuffLock *bl) {
    free(bl->buffer);
    free(bl->lock);
}

void *flipEndian(void *buff, int size) {
    char *p = malloc(size);
    for (int i = 0; i < size; i++) {
        ((char *) p)[i] = ((char *) buff)[size - i - 1];
    }
    return p;
}

void *inputThread(void *buffer) {
    BuffLock *buffLock = buffer;

    char *result = malloc(BUFF);
    int index = 0;
    int currentChar;

    while (runningMainThread) {
        currentChar = getchar();
        if (currentChar == 27) {
            runningMainThread = false;
            break;
        } else if (currentChar == 10) {
            if (pthread_mutex_lock(buffLock->lock) == 0) {
                Data *d = makeData(result, index);
                void *data = writeData(d);

                if (littleEndian()) {
                    flipEndian(data, index);
                }

                memcpy(buffLock->buffer, data, index + sizeof(int));
                memset(result, 0, BUFF);
                index = 0;
                free(data);
                freeData(d);

                pthread_mutex_unlock(buffLock->lock);
            }
        } else if (currentChar != -1) {
            result[index] = currentChar;
            index++;
        }
    }
}