#include "client.h"

Client *connectAsClient(char *ip) {
	Client *c = malloc(sizeof(*c));
	struct sockaddr_in *serverAddr;
	if (c == NULL) {
        return (NULL);
    }
	c->tv.tv_sec = 0;
	c->tv.tv_usec = 0;

	c->sock= socket(AF_INET, SOCK_STREAM, 0);

    serverAddr->sin_addr.s_addr = inet_addr(ip);
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(8080);
	
	if (connect(c->sock, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0) {
		printf("Connection failed\n");
		return (NULL);
	}
	return (c);
}

int receiveData(Client *c, void *buffer) {
	fd_set readfds;
	int res = 0;
	int activity = 0;

	FD_ZERO(&readfds);
	FD_SET(c->sock, &readfds);
	FD_SET(STDIN_FILENO, &readfds);
	activity = select(c->sock + 1, &readfds, NULL, NULL, NULL);
	if (activity >= 0) {
		if (c->sock > 0 && FD_ISSET(c->sock, &readfds)) {
			res = read(c->sock, buffer, BUFF);
			if (res == 1) {
				return (-1);
			}
		}
	}
	return (res);
}