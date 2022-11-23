#include "crypt.h"

Key *makeKeyPair() {
    Key *keyPair = malloc(sizeof(Key) * 2);
    if (keyPair == NULL) {
        return NULL;
    }
    keyPair[0] = makeKey();
    keyPair[1] = makeKey();
    return keyPair;
}

NUM *cryptData(NUM *data, int len, Key user) {
    NUM *cipher = malloc(sizeof(NUM) * len);
    if (cipher == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        cipher[i] = modExp(data[i], user.c, user.n);
    }
    return cipher;
}

void printKey(Key *k) {
    printf("Key: %d, %d\n", k->n, k->c);
}