#include "inputThread.h"
#include "data.c"

// Receives a shared buffer with a pthread_mutex_t stored in it.  Pull the pthread_mutex_t out and store it. Test your code to make sure that this lock is properly connected to the pthread_mutex_t being used in main.
// 	buffer is shared between this thread and the main thread. In a loop have this function take in user input and stores it in a buffer, when the user hits enter take in the string from the input buffer and copy it into the shared buffer via a Data struct. The main thread should then pick up that there is data in the buffer, and unpack it to display the string the user typed in.
// 	If the user hits the escape key have the program end. Hint take in the user input charavter at a time, rather than line by line.
void *inputThread(void *buffer) {
    pthread_mutex_t *lock = *(pthread_mutex_t**)buffer;
    char *inputBuffer = (char*)buffer + sizeof(pthread_mutex_t);
    bool running = true;
    while (running) {
        if (pthread_mutex_trylock(lock) == 0) {
            char c = getchar();
            if (c == '\n') {
                Data *d = makeData(inputBuffer, strlen(inputBuffer));
                void *dataBuffer = writeData(d);
                freeData(d);
                memcpy(inputBuffer, dataBuffer, d->bytes + sizeof(int));
                free(dataBuffer);
                memset(inputBuffer, 0, BUFF);
            } else if (c == 27) {
                running = false;
            } else {
                strncat(inputBuffer, &c, 1);
            }
            pthread_mutex_unlock(lock);
        }
    }
    pthread_exit(0);
}