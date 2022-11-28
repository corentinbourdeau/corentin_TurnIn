#include "networkCommand.h"

int main(int argc, char **argv) {
	srand(time(0));
	initBlockchain();
	ContactBook *contacts = getContacts();
	if (contacts->mainUser) {
		printf("welcome back %s\n\n", contacts->mainUser->name);
		timeToStart = true;
	} else {
		printf("no user.u found\nCreating new user please enter a name and press enter\n");
		timeToStart = false;
	}

	char *ip = 0;
	if (argc > 1) {
		ip = argv[1];
	}
	runNode(processBlockCommand, welcomeToBlockchain, parseCommand, ip);
	freeContacts(contacts);
	Blockchain *chain = getBlockchain();
	if (validateChain(chain)) {
		saveChain("blockchain.sav", chain);
	}
	freeBlockchain(chain);
}
