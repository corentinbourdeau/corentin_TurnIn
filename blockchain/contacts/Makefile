COM = gcc -Wall -w -pedantic -c -g
RM = rm -f

B = ../block/
S = $(B)sha256/
T = rsa/
D = ../../p2p/ex1/

contacts: main.c libBlock.a
	gcc -o contacts -g -Wall -w -pedantic main.c libBlock.a -lm

libBlock.a: sha256.o $(B)block.o contactBook.o $(T)crypt.o RSA.o $(T)transaction.o $(D)data.o
	ar rs libBlock.a $^

block.o: $(B)block.c $(B)block.h
	$(COM) $(B)block.c

sha256.o: $(S)sha256.c $(S)sha256.h
	$(COM) $(S)sha256.c 

contactBook.o: contactBook.c contactBook.h transactionPool.c transactionPool.h helper/list.c helper/list.h
	$(COM) $(C)contactBook.c

$(T)transaction.o: $(T)transaction.c $(T)transaction.h
	$(MAKE) transaction.o -C $(T)

$(T)crypt.o:  $(T)crypt.c $(T)crypt.h 
	$(MAKE) crypt.o -C $(T)

RSA.o: $(T)RSA/RSA.c $(T)RSA/RSA.h $(T)RSA/prime.c $(T)RSA/prime.h
	$(COM) $(T)RSA/RSA.c

$(D)data.o: $(D)data.c $(D)data.h
	$(MAKE) data.o -C $(D)

clean:
	$(RM) *.o
	$(MAKE) clean -C $(T)
	$(MAKE) clean -C $(D)
	$(MAKE) clean -C $(B)
	$(RM) *.a
	$(RM) vg*

fclean:
	$(RM) *.o
	$(MAKE) clean -C $(T)
	$(MAKE) clean -C $(D)
	$(MAKE) clean -C $(B)
	$(RM) *.a
	$(RM) contacts
	$(RM) *.sav
	$(RM) *.u
	$(RM) vg*
