#include "RSA.h"
#include "prime.c"

NUM *genKeys(NUM prime1, NUM prime2) {
	NUM n = prime1 * prime2;
	NUM phi = (prime1 - 1) * (prime2 - 1);
	NUM e = 65537;
	NUM d = get_d(e, phi);
	NUM *keys = (NUM*)calloc(3, sizeof(NUM));

	//1st is the public key
	keys[0] = n;
	keys[1] = e;
	//2nd is the private key
	keys[2] = d;
	return keys;
}

NUM get_d(NUM e, NUM phi){
	EE ee;
	ee = extended_euclid(e, phi);
	return modulo(ee.x, phi);	
}

EE extended_euclid(NUM a, NUM b) {
	EE ee1, ee2, ee3;
	if (b == 0) {
		ee1.d = a;
		ee1.x = 1;
		ee1.y = 0;
		return ee1;
	} else {
		ee2 = extended_euclid(b, a % b);
		ee3.d = ee2.d;
		ee3.x = ee2.y;
		ee3.y = ee2.x - floor(a / b) * ee2.y;
		return ee3;
	}
}

NUM modulo(NUM x, NUM N) {
    return (x % N + N) % N;
}

void decimal_to_binary(NUM op1, NUM aOp[]) {
    NUM result, i = 0;
    do{
        result = op1 % 2;
        op1 /= 2;
        aOp[i] = result;
        i++;
    }while(op1 > 0);
}

NUM modular_exponentiation(NUM a, NUM b, NUM n) {
	NUM *bb;
	NUM count = 0, c = 0, d = 1, i;

	// find out the size of binary b
	count = (NUM) (log(b)/log(2)) + 1;

	bb = (NUM *) malloc(sizeof(NUM*) * count);
	decimal_to_binary(b, bb);

	for (i = count - 1; i >= 0; i--) {
		c = 2 * c;
		d = (d*d) % n;
		if (bb[i] == 1) {
			c = c + 1;
			d = (d*a) % n;
		}
	}
	free(bb);
	return d;
}
