#ifndef CONTACTBOOK
#define CONTACTBOOK
#include "../block/block.h"
#include "rsa/transaction.h"
#include "../../ex2/node.h"
#include "helper/list.h"

typedef struct Contact {
	char *name;
	Key publicKey;
} Contact;

typedef struct User {
	char *name;
	Key publicKey;
	Key privateKey;
} User;

typedef struct ContactBook {
	linkedList *book[27];
	User *mainUser;
	linkedList *transactionPool;
} ContactBook;

#include "transactionPool.h"

ContactBook *initContacts();
void freeContacts();

User *genUser(char *name);
void freeUser(User *u);
void *packUser(User *u);
User *unpackUser(void *buffer);
void saveUser(char *file, User *u);

Contact *getContact(User *u);
void *packContact(Contact *c);
Contact *unpackContact(void *buffer);

User *loadUser(char *file);
Contact *makeContact(char *name, Key key);

bool addToContacts(ContactBook *contacts, Contact *c);
void printContacts(ContactBook *contacts);

Contact *findContact(ContactBook *contacts, Key publicKey);
Contact *findContactName(ContactBook *contacts, char *name);

void freeContact(Contact *c);
int contactLength(Contact *c);
void printUser(User *u);
void printContact(Contact *c);
#endif
