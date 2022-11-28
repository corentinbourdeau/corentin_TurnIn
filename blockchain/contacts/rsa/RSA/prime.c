void writeArr(char *file, NUM *arr, NUM num) {
	FILE *fptr = fopen(file, "w");
	if (fptr != NULL) {
		size_t elementSize = sizeof(NUM);
		size_t elementNum = num;
		NUM *buff = (NUM *)calloc(num + 1, sizeof(NUM));
		buff[0] = num;
		memcpy(buff + 1, arr, sizeof(NUM) * num);
		size_t elementsWritten = fwrite(buff, elementSize, elementNum + 1, fptr);
		free(buff);
		fclose(fptr);
	}
}

NUM readArr(char *file, NUM **arr) {//,  int num) {
	FILE *fptr = fopen(file, "r");
	if (fptr != NULL) {	
		NUM num = 0;
		fread(&num, sizeof(NUM), 1, fptr);
		//prNUMf("got number %d\n", num);
		*arr = (NUM*)calloc(num, sizeof(NUM));
		fread(*arr, sizeof(NUM), num, fptr);
		fclose(fptr);
		return num;
	}
	return 0;
}

bool isPrime(NUM n) {
	bool prime = true;
	for (NUM i = 2; i < n; i++) {
		if ((n % i) == 0) {
			return false;
		}
	}
	return true;
}

NUM *genPrimes(NUM min, NUM max) {
	NUM *arr = (NUM*)calloc(max-min, sizeof(NUM));
	NUM count = 0;
	for (NUM i = min; i <= max; i++) {
		if (isPrime(i)) {
			arr[count] = i;
			count++;
		}
	}
	NUM *primes = (NUM *)calloc(count, sizeof(NUM));
	memcpy(primes, arr, count * sizeof(NUM));
	free(arr);
	writeArr("primes", primes, count);
}

NUM randomPrime() {
	NUM *arr = 0;
	int num = readArr("primes", &arr);
	if (num != 0) {
		bool largeHalf = (rand() % 2) == 0;
		int r = rand() % num;//(rand() + (largeHalf * (num/2))) % num;
		NUM prime = arr[r];
		
		free(arr);
		return prime;
	} else {
		printf("could not open primes file\n");
		return 0;
	}
}

