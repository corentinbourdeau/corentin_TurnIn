#include "transaction.h"

NUM *signTransaction(Key *sender, Key recipient, float amount) {
    NUM *transaction = malloc(sizeof(NUM) * 4);
    if (transaction == NULL) {
        return NULL;
    }
    transaction[0] = sender[0].n;
    transaction[1] = sender[0].c;
    transaction[2] = recipient.n;
    transaction[3] = recipient.c;
    transaction[4] = amount;
    transaction[5] = time(NULL);
    NUM *cipher = cryptData(transaction, 6, sender[1]);
    free(transaction);
    return cipher;
}


Transaction *decryptTransaction(NUM *transaction, Key sender) {
    NUM *cipher = cryptData(transaction, 6, sender);
    if (cipher[0] != sender.n || cipher[1] != sender.c) {
        free(cipher);
        return NULL;
    }
    Transaction *t = malloc(sizeof(Transaction));
    if (t == NULL) {
        free(cipher);
        return NULL;
    }
    t->sender.n = cipher[0];
    t->sender.c = cipher[1];
    t->recipient.n = cipher[2];
    t->recipient.c = cipher[3];
    t->amount = cipher[4];
    t->timestamp = cipher[5];
    free(cipher);
    return t;
}

void printTransaction(Transaction *t) {
    printf("Sender: %d, %d Recipient: %d, %d Amount: %f Timestamp: %d \n", t->sender.n, t->sender.c, t->recipient.n, t->recipient.c, t->amount, t->timestamp);
}