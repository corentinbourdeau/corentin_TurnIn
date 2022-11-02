#include "inputThread.h"
#include "data.c"

void *inputThread(void *buffer) {
    pthread_mutex_t *lock = (pthread_mutex_t *) buffer;
    char *input = calloc(1, sizeof(char));
    char *inputBuffer = calloc(1, sizeof(char));
    int i = 0;
    bool runningMainThread = true;
    while (runningMainThread) {
        char c = getchar();
        if (c == 27) {
            runningMainThread = false;
            break;
        }
        if (c == 10) {
            if (pthread_mutex_trylock(lock) == 0) {
                Data *d = makeData(inputBuffer, i);
                memcpy(buffer, d, sizeof(Data));
                pthread_mutex_unlock(lock);
                i = 0;
                free(inputBuffer);
                inputBuffer = calloc(1, sizeof(char));
            }
        } else {
            inputBuffer[i] = c;
            i++;
            inputBuffer = realloc(inputBuffer, i + 1);
        }
    }
    free(input);
    free(inputBuffer);
}