#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct Server {
	int sock;
	int maxClients;
	int *clientSocks;
	int addrlen;
	struct sockaddr_in addr;
	struct timeval tv;
} Server;

#define BUFF 1024

extern void *welcomeMessage;
extern int welcomeSize;
extern Server *s;
