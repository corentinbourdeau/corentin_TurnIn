#include "data.h"

bool littleEndian() {
    int i = 1;
    char *p = (char *) &i;
    return (int)*p;
}

Data *makeData(void *dat, int bytes) {
    Data *d = (Data *) malloc(sizeof(Data));
    d->arr = malloc(bytes);
    memcpy(d->arr, dat, bytes);
    d->bytes = bytes;
    return d;
}

void *writeData(Data *d) {
    void *buffer = calloc(d->bytes + sizeof(int), 1);
    memcpy(buffer, &d->bytes, sizeof(int));
    memcpy(buffer + sizeof(int), d->arr, d->bytes);
    return buffer;
}

Data *readData(void *buffer) {
    Data *d = (Data *) malloc(sizeof(Data));
    memcpy(&d->bytes, buffer, sizeof(int));
    d->arr = calloc(d->bytes, 1);
    memcpy(d->arr, buffer + sizeof(int), d->bytes);
    return d;
}

void freeData(Data *d) {
    free(d->arr);
    free(d);
}

void *flipEndian(void *buff, int size) {
    void *newBuff = malloc(size);
    for (int i = 0; i < size; i++) {
        ((char *) newBuff)[i] = ((char *) buff)[size - i - 1];
    }
    return newBuff;
}
