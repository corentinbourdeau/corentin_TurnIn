#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include "sha256/sha256.h"
#include "../ex1/data.h"

typedef struct Block {
	int index;
	BYTE preHash[SHA256_BLOCK_SIZE]; 	//macros provided in header
	BYTE dataHash[SHA256_BLOCK_SIZE];
	Data *data; 	// pointer to data stored in this block
	int nonce; 	// int representing the proof of work validating this block
	time_t timestamp;
	struct Block *next; 	// next block in the chain
} Block;

typedef struct Blockchain {
	Block * base; 		//genesis block of the chain, unchanged once chain is initialized
	Block *cur;		// the current top of the chain, used for addition of new blocks
	int len;			// the number of blocks in the chain
} Blockchain;

Block *makeBlock(Data *d, Block *pre);
Blockchain *makeBlockchain();
bool addBlock(Blockchain *bc, Block *b);
bool validateChain(Blockchain *bc);
void printBlock(Block *b);
void printChain(Blockchain *bc, , void (*printFunc)(Block*));
void freeBlockchain(Blockchain *bc);
void saveChain(char *file, Blockchain *bc);
Blockchain *loadChain(char *file);