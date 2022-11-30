#include "networkCommand.h"

Blockchain *initBlockchain() {
    Blockchain *bc = makeBlockchain();
    Data *d = makeData("Genesis Block", "Genesis Block", 0);
    Block *b = makeBlock(d, NULL);
    addBlock(bc, b);
    return bc;
}
	// Initializes global myChain variable, attempting to load from the disk. Additionally it initialises the global contacts struct.

Blockchain *getBlockchain() {
    return myChain;
}
	// returns a pointer to the global myChain Blockchain struct.

ContactBook *get Contacts() {
    return contacts;
}
	// returns a pointer to the global conacts ContactBook struct.

void welcomeToBlockchain() {
    printf("Welcome to Blockchain\n");
}
	// Called from runNode as welcome. This is called when the server is set up and it packs in the servers contact message, to be ready to be sent to any client that connects.

void parseCommand(char *str) {
    printf("parseCommand: %s, port: %d\n", str, mainUser->port);
    if (strcmp(str, "mine") == 0) {
        mineBlock();
    } else if (strcmp(str, "print") == 0) {
        printBlockchain();
    } else if (strcmp(str, "balance") == 0) {
        printBalance();
    } else if (strcmp(str, "exit") == 0) {
        exit(0);
    } else {
        newTransaction(str);
    }
}
	// Called from runNode as parse. This is called whenever the user thread has new data in its buffer. That data passed to this function via str. The function then takes that string and parses it for user commands on the blockchain. 
	// You must include commands for mining new blocks, sending transactions, printing out the blockchain, and printing out the main user’s account balance. In addition to this when the program starts up the user will enter a name and it must be used to generate a User struct to be used as mainUser.

void processData(void *buffer, bool onServer) {
    Data *d = parseDataMessage(buffer);
    if (d->mes == 0) {
        // Contact
        Contact *c = d->data;
        addContact(contacts, c);
        if (onServer) {
            Data *d = myContactMessage();
            sendToClient(d);
        }
    } else if (d->mes == 1) {
        // Transaction
        Transaction *t = d->data;
        if (verifyTransaction(t)) {
            addTransaction(myChain, t);
        }
    } else if (d->mes == 2) {
        // Block
        Block *b = d->data;
        if (verifyBlock(b)) {
            addBlock(myChain, b);
        }
    } else if (d->mes == 3) {
        // Blockchain
        Blockchain *b = d->data;
        if (b->length > myChain->length) {
            myChain = b;
        }
    } else if (d->mes == 4) {
        // Chain Length
        if (onServer) {
            Data *d = chainLengthMessage(myChain);
            sendToClient(d);
        }
    }
}

Data *writeDataMessage(int mes, Data *d) {
    Data *data = malloc(sizeof(Data));
    data->mes = mes;
    data->data = d;
    return data;
}
	// creates a data packet with mes attached to the front of the buffer, so it explicitly tell others across the network what is inside. mes corresponds to different types of events that are to be broadcast.

Data *parseDataMessage(void *buffer) {
    Data *d = malloc(sizeof(Data));
    d->mes = *(int *)buffer;
    d->data = buffer + sizeof(int);
    return d;
}
	// unpacks the buffer, pulls out mes and then unpacks the rest it into whatever struct its supposed to be (Contact, Transaction, Block, Blockchain etc) as told by mes

Data*chainLengthMessage(Blockchain *chain) {
    int *length = malloc(sizeof(int));
    *length = chain->length;
    return writeDataMessage(4, length);
}
	// packs up the length of local chain

Data *myContactMessage() {
    return writeDataMessage(0, mainUser);
}
	// packs up the main User’s contact

Data *newBlockMessage() {
    Block *b = mineBlock();
    return writeDataMessage(2, b);
}
	// mines a fresh block and packs it up to be broadcast
 
Data *newTransactionMessage(char *com) {
    Transaction *t = newTransaction(com);
    return writeDataMessage(1, t);
}
	// creates a transaction from command string, verifies it and packs it up

Data *BlockchainMessage(Blockchain *chain) {
    return writeDataMessage(3, chain);
}
	// packs up the Blockchain to sent over the network