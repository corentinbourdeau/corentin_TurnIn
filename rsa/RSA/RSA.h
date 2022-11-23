#ifndef RSA
#define RSA
#include "prime.h"
#include <math.h>
#include <stdlib.h>

typedef struct {
	NUM d;
	NUM x;
	NUM y;
} EE;

NUM *genKeys(NUM prime1, NUM prime2);
EE extended_euclid(NUM a, NUM b);
NUM modulo(NUM x, NUM N);
void decimal_to_binary(NUM op1, NUM aOp[]);
NUM get_d(NUM e, NUM phi);
NUM modular_exponentiation(NUM a, NUM b, NUM n);
#endif
