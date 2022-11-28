#ifndef TRANSACTIONPOOL
#define TRANSACTIONPOOL
#define POOLSIZE 3

NUM *genTransaction(User *u, Contact *c, float amount);
bool verifyTransaction(ContactBook *contacts, NUM *t, Key k, Blockchain *bc);
Block *mineBlock(ContactBook *contacts, Blockchain *bc, Contact *miner);
void printPoolPack (Block *b);
float accountBalance(ContactBook *contacts, Key account, Blockchain *bc);
bool chooseChain(ContactBook *contacts, Blockchain **curChain, Blockchain *newChain);

void addToPool(ContactBook *contacts, Transaction *t);
bool searchForTransaction(ContactBook *contacts, Transaction *t);
bool removeFromTransactions(ContactBook *contacts, Transaction *t);
void printTransactionPool(ContactBook *contacts);

#endif
