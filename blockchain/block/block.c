#include "block.h"

Block *makeBlock(Data *d, Block *pre) {
    Block *b = (Block *)malloc(sizeof(Block));
    b->data = d;
    b->nonce = 0;
    b->preHash = (BYTE *)malloc(sizeof(BYTE) * 32);
    b->dataHash = (BYTE *)malloc(sizeof(BYTE) * 32);
    b->hash = (BYTE *)malloc(sizeof(BYTE) * 32);
    if (pre == NULL) {
        b->preHash = NULL;
    } else {
        hashBlock(pre, b->preHash);
    }
    hashBlockData(b, b->dataHash);
    while (true) {
        hashBlock(b, b->hash);
        if (b->hash[0] == 0 && b->hash[1] == 0 && b->hash[2] == 0) {
            break;
        }
        b->nonce++;
    }
    return b;
}

Blockchain *makeBlockchain() {
    Blockchain *bc = (Blockchain *)malloc(sizeof(Blockchain));
    bc->head = NULL;
    bc->cur = NULL;
    bc->size = 0;
    return bc;
}

bool addBlock(Blockchain *bc, Block *b) {
    if (bc->head == NULL) {
        bc->head = b;
        bc->cur = b;
        bc->size++;
        return true;
    }
    if (b->preHash == NULL) {
        return false;
    }
    if (memcmp(b->preHash, bc->cur->hash, 32) != 0) {
        return false;
    }
    bc->cur->next = b;
    bc->cur = b;
    bc->size++;
    return true;
}

bool validateChain(Blockchain *bc) {
    Block *cur = bc->head;
    while (cur != NULL) {
        if (cur->preHash != NULL) {
            BYTE *hash = (BYTE *)malloc(sizeof(BYTE) * 32);
            hashBlock(cur, hash);
            if (memcmp(cur->preHash, hash, 32) != 0) {
                return false;
            }
        }
        cur = cur->next;
    }
    return true;
}

void printBlock(Block *b) {
    printf("Block %d, hash %s\n", b->hash, b->preHash);
}

void printChain(Blockchain *bc, , void (*printFunc)(Block*)) {
    Block *cur = bc->head;
    while (cur != NULL) {
        printFunc(cur);
        cur = cur->next;
    }
}

void freeBlockchain(Blockchain *bc) {
    Block *cur = bc->head;
    while (cur != NULL) {
        Block *next = cur->next;
        free(cur);
        cur = next;
    }
    free(bc);
}

void saveChain(char *file, Blockchain *bc) {
    FILE *fp = fopen(file, "w");
    Block *cur = bc->head;
    while (cur != NULL) {
        fwrite(cur, sizeof(Block), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
}

Blockchain *loadChain(char *file) {
    Blockchain *bc = makeBlockchain();
    FILE *fp = fopen(file, "r");
    while (true) {
        Block *b = (Block *)malloc(sizeof(Block));
        if (fread(b, sizeof(Block), 1, fp) != 1) {
            free(b);
            break;
        }
        addBlock(bc, b);
    }
    fclose(fp);
    return bc;
}