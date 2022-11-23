#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

typedef struct Transaction {
	Key sender;
	Key recipient;
	float amount;
	time_t timestamp;
} Transaction;

NUM *signTransaction(Key *sender, Key recipient, float amount);
	// This function will takee in the information needed for a Transaction, but it doesn’t need to be put into a struct here, instead we can store it in an array. sender will be an array containing both public and private key. The public key will be put into the array along with  recipient, which corresponds to the recipients public key. The amount will be put in and a timestamp will be generated and put into the  array. Then you will use the sender’s private key to encrypt the array and return it from the function. If this fails at any point it should free all allocated memory within and return NULL.

Transaction *decryptTransaction(NUM *transaction, Key sender);
	// This function will take in cipher array created from signTransaction as well as the sender’s public Key. Using the cryptData function it will decrypt the transaction cipher and store the values into a Transaction struct. Since we have a copy of the public key sent to us, we can verify that this cipher was decrypted properly by comparing the the decrypted key to the provided key. If they do not match we know the transaction has been tampered with, free all memory and return NULL. But if the the Keys do match return a pointer to the newly created struct.

void printTransaction(Transaction *t);
	// prints out the details of the transaction. 