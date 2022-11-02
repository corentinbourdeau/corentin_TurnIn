#include "data.h"

bool littleEndian() {
    int i = 1;
    char *p = (char *) &i;
    return (int)*p;
}

Data *makeData(void *dat, int bytes) {
    Data *d = (Data *) malloc(sizeof(Data));
    d->arr = dat;
    d->bytes = bytes;
    return d;
}

void *writeData(Data *d) {
    void *dat = malloc(d->bytes);
    memcpy(dat, d->arr, d->bytes);
    return dat;
}

Data *readData(void *buffer) {
    Data *d = (Data *) malloc(sizeof(Data));
    memcpy(&d->bytes, buffer, sizeof(int));
    d->arr = malloc(d->bytes);
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
