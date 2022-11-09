#include "client.h"

Client *connectAsClient(char *ip) {
	Client *client = malloc(sizeof(Client));

	if (client == NULL) {
        return (NULL);
    }
	client->sock = socket(AF_INET, SOCK_STREAM, 0);
	client->tv.tv_sec = 0;
	client->tv.tv_usec = 0;

	struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(client->sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		printf("Connection to connect to %s\n", ip);
		return (NULL);
	}
	printf("Connection to the server\n");
	return (client);
}

int receiveData(Client *c, void *buffer) {
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(c->sock, &readfds);
	int activity = select(c->sock + 1, &readfds, NULL, NULL, &c->tv);
	if (activity < 0) {
		printf("Error selecting socket");
		return (-1);
	}
	else if (activity > 0) {
		int size = read(c->sock, buffer, BUFF);
		return (size);
	}
	return (0);
}