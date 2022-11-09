#include "data.h"

bool runningMainThread;

bool littleEndian() {
    union {
        uint32_t i;
        char c[4];
    } e = { 0x01000000 };

    return e.c[0] ? false : true;
}

Data *makeData(void *dat, int bytes) {
    Data *d = malloc(sizeof(Data));

    d->bytes = bytes;
    d->arr = malloc(bytes);
    memcpy(d->arr, dat, bytes);

    return d;
}

void *writeData(Data *d) {
    void *buffer = malloc(d->bytes + sizeof(int));

    memcpy(buffer, &d->bytes, sizeof (int));
    memcpy(buffer + sizeof (int), d->arr, d->bytes);

    return buffer;
}

Data *readData(void *buffer) {
    int bytes = 0;
    memcpy(&bytes, buffer, sizeof(int));
    if (bytes == 0) {
        return 0;
    }
    Data *d = (Data*)calloc(1, sizeof(Data));
    d->bytes = bytes;
    d->arr = calloc(1, bytes);
    memcpy(d->arr, buffer + sizeof(int), bytes);
    return d;
}

void freeData(Data *d) {
    free(d->arr);
    free(d);
}
