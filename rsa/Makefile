COM = gcc -c -g -Wall -w -pedantic
RM = rm -f

transaction: main.c libTransaction.a
	gcc -g -o transaction main.c libTransaction.a -lm    

libTransaction.a: transaction.o crypt.o RSA.o
	ar rs libTransaction.a $^

transaction.o: transaction.c transaction.h
	$(COM) transaction.c

crypt.o: crypt.c crypt.h
	$(COM) crypt.c

RSA.o: RSA/RSA.c RSA/RSA.h RSA/prime.c RSA/prime.h
	$(COM) RSA/RSA.c

clean:
	$(RM) *.o
	$(RM) *.a

fclean:
	$(RM) *.o
	$(RM) *.a
	$(RM) transaction
	$(RM) vg*
