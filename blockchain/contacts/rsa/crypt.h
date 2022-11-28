#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

//struct holding the values for a key, can be private or public
typedef struct Key {
	NUM n;
	NUM c;
} Key;

Key *makeKeyPair();
	// generates 2 random prime numbers and passes them to provided genKeys function which returns an array of 3 integers. publicKey.n = [0], pubicKey.c = [1] privateKey.n = [0]  and privateKey.c = [2]. Store them accordingly into an array of Key structs of size 2.

NUM *cryptData(NUM *data, int len, Key user);
	// Takes in an array of type defined by NUM macro and the length of that array. It also takes in the key to be used for this data. The provided modularExponentiation function will encrypt/decrypt a chunk of data sized as NUM(in the standard case 8 bytes);
// The user Key’s values will be used in the modularExponentiation function. If you pass in a message that message will be encrypted. If you pass in a cipher and the corresponding Key used to create the cipher it will decrypt it. If you send in the wrong key, you simply get gibberish.

void printKey(Key *k);
	// print out both n and c of the Key passed to it. Remember NUM is default type int64_t. (printf(“%”PRId64”\n”);)
