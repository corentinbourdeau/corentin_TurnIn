#include "contactBook.h"

int charToIndex(char c) {
	char alph = c;
	if (alph >= 65 && alph <= 90) {
		alph -= 65;	
	} else if (alph >= 97 && alph <= 122) {
		alph -= 97;
	} else {
		alph = 26;
	}
	return alph;
}

bool addToContacts(ContactBook *contacts, Contact *c) {
	int alph = charToIndex(c->name[0]);
	linkedList **cur = &(contacts->book[alph]);
	linkedList **pre = cur;
	while (*cur) {
		Contact *curCon = (Contact*)(*cur)->data;
		if (!compareKeys(curCon->publicKey, c->publicKey)) {
			pre = cur;
			cur = &((*cur)->next);
		} else {
			return false;
		}
	}
	*cur = (linkedList*)calloc(1, sizeof(linkedList));
	(*cur)->data = makeContact(c->name, c->publicKey);
	contacts->byteSize += contactLength(c);
	if (pre && pre != cur) {
		(*pre)->next = *cur;
	}
	return true;
}

Contact *findContactName(ContactBook *contacts, char *name) {
	int alph = charToIndex(*name);
	linkedList *cur = contacts->book[alph];
	while (cur) {
		if (cur->data) {
			Contact *c = cur->data;
			if (strcmp(name, c->name) == 0) {
				return c;
			}
		}
		cur = cur->next;
	}
	return 0;
}


Contact *findContact(ContactBook *contacts, Key publicKey) {
	for (int i = 0; i < 27; i++) {	
		linkedList *cur = contacts->book[i];
		while (cur) {
			if (cur->data) {
				Contact *c = cur->data;
				if (compareKeys(c->publicKey, publicKey)) {
					return c;
				}
			}
			cur = cur->next;
		}
	}
}


void printContacts(ContactBook *contacts) {
	if (contacts) {
		printf("----CONTACTS----\n|\n");
		for (int i = 0; i < 27; i++) {
			if (contacts->book[i]) {
				linkedList *cur = contacts->book[i];
				if (i < 26) {
					printf("----PAGE_%c----\n", i + 65);
				} else {
					printf("----PAGE_*----\n");
				}
				while (cur) {
					if (cur->data) {
						printContact(cur->data);
					}
					cur = cur->next;
				}
				printf("----______----\n|\n");
			}
		}
		printf("\n");
	}
}

void saveContacts(ContactBook *contacts) {
	FILE *fptr = fopen("contacts.sav", "w");
	if (fptr != NULL) {
		printf("%i\n", contacts->byteSize);
		void *buffer = calloc(1, contacts->byteSize + sizeof(int));
		memcpy(buffer, &(contacts->byteSize), sizeof(int));
		void *tmp = buffer + sizeof(int);
		for (int i = 0; i < 27; i++) {
			linkedList *cur = contacts->book[i];
			while(cur) {
				if (cur->data) {
					int len = contactLength(cur->data);
					void *b = packContact(cur->data);
					memcpy(tmp, b, len);
					free(b);
					tmp += len;
				}
				cur = cur->next;
			}
		}
		fwrite(buffer, contacts->byteSize + sizeof(int), 1, fptr);
		free(buffer);
		fclose(fptr);
	}
}

ContactBook *loadContacts() {
	FILE *fptr = fopen("contacts.sav", "r");
	ContactBook *contacts = 0;
	if (fptr != NULL) {
		int size = 0;
		fread(&size, sizeof(int), 1, fptr);
		void *buff = calloc(1, size);
		fread(buff, size, 1, fptr);
		fclose(fptr);
		void *tmp = buff;
		while (tmp - buff < size) {
			Contact *c = unpackContact(tmp);
			addToContacts(contacts, c);
			tmp += contactLength(c);
		}
		free(buff);
	}
	return contacts;
}

int contactLength(Contact *c) {
	return sizeof(int) + strlen(c->name) + 1 + sizeof(Key);
}

void printUser(User *u) {
	printf("User:\n%s\n", u->name);
	printf("Private Key: (n = %"PRId64", d = %"PRId64")\n", u->privateKey.n, u->privateKey.c);
	printf("Public Key: (n = %"PRId64", d = %"PRId64")\n", u->publicKey.n, u->publicKey.c);

}


void printContact(Contact *c) {
	printf("Contact:\n%s\n", c->name);
	printf("Public Key: (n = %"PRId64", c = %"PRId64")\n", c->publicKey.n, c->publicKey.c);
}

void freeContact(Contact * c) {
	free(c->name);
	free(c);
}

#include "helper/list.c"
#include "transactionPool.c"
