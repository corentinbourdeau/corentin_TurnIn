void addToPool(ContactBook *contacts, Transaction *t) {
	Transaction *trans = calloc(1, sizeof(Transaction));
	memcpy(trans, t, sizeof(Transaction));
	addToList(&contacts->transactionPool, trans);
}

bool searchForTransaction(ContactBook *contacts, Transaction *t) {
	return cmpList(&contacts->transactionPool, t, compareTransactions);
}

bool removeFromTransactions(ContactBook *contacts, Transaction *t) {
	Transaction *removed = removeFromList(&contacts->transactionPool, t);
	if (removed) {
		return true;
	} else {
		return false;
	}
}

void printTransactionPool(ContactBook *contacts) {
	printList(&contacts->transactionPool, "Transaction Pool", printTransaction);
}

