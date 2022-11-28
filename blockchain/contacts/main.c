#include "contactBook.h"

int main() {
	srand(time(0));
	Blockchain *myChain = loadChain("blockchain.sav");
	if (!myChain) {
		myChain = makeBlockchain();
	}
	ContactBook *book = initContacts();
	if (book->mainUser) {
		printf("welcome back %s\n\n", book->mainUser->name);
	} else {
		printf("no user.u found\nCreating new user please enter a name and press enter\n");
		char name[1024];
		scanf("%s", name);
		book->mainUser = genUser(name);
		printUser(book->mainUser);
		void *buff = packUser(book->mainUser);
		User *u = unpackUser(buff);
		free(buff);
		printUser(u);
		freeUser(u);
		saveUser("user.u", book->mainUser);
	}
	User *recipient = genUser("Ron");
	Contact *c = getContact(recipient);
	freeUser(recipient);
	addToContacts(book, c);
	printContacts(book);
	NUM *tHash = genTransaction(book->mainUser, c, 0);
	verifyTransaction(book, tHash, book->mainUser->publicKey, myChain);
	free(tHash);
	printTransactionPool(book);
	Contact *miner = getContact(book->mainUser);
	Block *b = mineBlock(book, myChain, miner);
	if (b) {
		if (addBlock(myChain, b)) {
			printf("successfully mined a block\n-----\n");
			printPoolPack(myChain->cur);
		}
	}
	printf("your account balance is now %f\n", accountBalance(book, miner->publicKey, myChain));	
	NUM *tHash2 = genTransaction(book->mainUser, c, 10);
	verifyTransaction(book, tHash2, book->mainUser->publicKey, myChain);

	Blockchain *other = makeBlockchain();
	/* CHOOSE CHAIN */
	sleep(1);
	for (int i = 0; i < 2; i++) {
		NUM *tHash = genTransaction(book->mainUser, c, 0);
		verifyTransaction(book, tHash, book->mainUser->publicKey, myChain);
		free(tHash);
		Block *b = mineBlock(book, other, miner);
		if (b) {
			addBlock(other, b);
		}
	}
	if (chooseChain(book, &myChain, other)) {
		printf("new chain chosen\n");
	} else {
		printf("current chain kept\n");
	}
	b = mineBlock(book, myChain, miner);
	if (b) {
		addBlock(myChain, b);
	}
	free(tHash2);
	freeContact(c);
	freeContact(miner);
	freeContacts(book);

	printChain(myChain, printPoolPack);

	if (validateChain(myChain)) {
		saveChain("blockchain.sav", myChain);
	}
	freeBlockchain(myChain);
	
	return 0;
}
