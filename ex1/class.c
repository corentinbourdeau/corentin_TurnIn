#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock;

void *func(void *data) {
    int *num= calloc(1, sizeof(int));
    memcpy(num, data, sizeof(int));
    // printf("Got number %i\n", *num);
    int i = 0;
    while (i < 5) {
        if (pthread_mutex_trylock(&lock) == 0) {
            printf("%i\n", *num);
            *num+=2;
            sleep(1);
            pthread_mutex_unlock(&lock);
            i++;
        }
    }
    return num;
}

int main() {
    pthread_t handle1;
    pthread_t handle2;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }

    int num1 = 0;
    pthread_create(&handle1, &attr, func, &num1);
    printf("Thread 1 created\n");
    int num2 = 1;
    pthread_create(&handle2, &attr, func, &num2);

    void *v1;
    void *v2;
    pthread_join(handle1, &v1);
    printf("Thread 1 counted to %i\n", *(int*)v1);
    pthread_join(handle2, &v2);
    printf("Thread 2 counted to %i\n", *(int*)v2);

    free(v1);
    free(v2);
    pthread_exit(0);
}