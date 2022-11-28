// these globals should only be accessible within this file and used only on this thread
#include "block/block.h"
#include "contacts/contactBook.h"
Blockchain *myChain;
ContactBook *contacts;

Blockchain *initBlockchain();
	// Initializes global myChain variable, attempting to load from the disk. Additionally it initialises the global contacts struct.

Blockchain *getBlockchain();
	// returns a pointer to the global myChain Blockchain struct.

ContactBook *get Contacts();
	// returns a pointer to the global conacts ContactBook struct.

welcomeToBlockchain();
	// Called from runNode as welcome. This is called when the server is set up and it packs in the servers contact message, to be ready to be sent to any client that connects.

void parseCommand(char *str);
	// Called from runNode as parse. This is called whenever the user thread has new data in its buffer. That data passed to this function via str. The function then takes that string and parses it for user commands on the blockchain. 
	// You must include commands for mining new blocks, sending transactions, printing out the blockchain, and printing out the main user’s account balance. In addition to this when the program starts up the user will enter a name and it must be used to generate a User struct to be used as mainUser.

void processData(void *buffer, bool onServer);
	// Called from runNode as processData. This functions takes in buffers from the client and or server and processes the data inside of it into the proper functions. If there is a Transaction received from the network it is verified and added to the transaction pool. If a Block is received it is validated and added to the chain.
	// Some data may recquire a response to be sent to the network. If you receive a Contact you should send your local Contact back. If you receive a blockchain length, you should send your own back, or perhaps your whole chain if your length is bugger. Any response data should be sent along to the client and or server.q

Data *writeDataMessage(int mes, Data *d);
	// creates a data packet with mes attached to the front of the buffer, so it explicitly tell others across the network what is inside. mes corresponds to different types of events that are to be broadcast.

Data *parseDataMessage(void *buffer);
	// unpacks the buffer, pulls out mes and then unpacks the rest it into whatever struct its supposed to be (Contact, Transaction, Block, Blockchain etc) as told by mes

Data*chainLengthMessage(Blockchain *chain);
	// packs up the length of local chain

Data *myContactMessage();
	// packs up the main User’s contact

Data *newBlockMessage();
	// mines a fresh block and packs it up to be broadcast
 
Data *newTransactionMessage(char *com);
	// creates a transaction from command string, verifies it and packs it up

Data *BlockchainMessage(Blockchain *chain);
	// packs up the Blockchain to sent over the network