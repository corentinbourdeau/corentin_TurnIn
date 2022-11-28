#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include<inttypes.h>
#include <math.h>

#include "RSA/RSA.h"

int main() {
	srand(time(0));
	NUM p1 = randomPrime();
	NUM p2 = randomPrime();
	printf("%"PRId64" and %"PRId64"\n", p1, p2);

	NUM *keys = genKeys(p1, p2);
	NUM mes = 12131;
	NUM ciph = modular_exponentiation(mes, keys[2], keys[0]);
	NUM decrypt = modular_exponentiation(ciph, keys[1], keys[0]);
	printf("og:%"PRId64", ciph: %"PRId64", dec: %"PRId64"\n", mes, ciph, decrypt);

	p1 = randomPrime();
	p2 = randomPrime();
	NUM *keys2 = genKeys(p1, p2);
	decrypt = modular_exponentiation(ciph, keys2[1], keys2[0]);
	printf("og:%"PRId64", ciph: %"PRId64", dec: %"PRId64"\n", mes, ciph, decrypt);

	ciph = modular_exponentiation(keys[0], keys[2], keys[0]);
	decrypt = modular_exponentiation(ciph, keys[1], keys[0]);
	printf("og:%"PRId64", ciph: %"PRId64", dec: %"PRId64"\n", keys[0], ciph, decrypt);
	return 0;
}

