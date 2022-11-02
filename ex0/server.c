#include "server.h"

// Server
// typedef struct Server {
// 	int sock;
// 	int maxClients;
// 	int *clientSocks;
// 	int addrlen;
// 	struct sockaddr_in addr;
// 	struct timeval tv;
// } Server;

// #define BUFF 1024
// 	macro defining buffer size.

// extern void *welcomeMessage;
// extern int welcomeSize;
// extern Server *s;

// Server* setUpConnections();
// 	This function will initialize the server struct. clientSocks will be initialized to the size of maxClients (at least 10). timeval can be set to 0 seconds. sock will be initialized with the file descriptor you get from creating a socket. We will be using the communication domain AF_INET. The socket will be of type SOCK_STREAM.
// 	You will probably want to set socket options to allow multiple connections. addr will be set to use any address.
// 	The function will bind the socket to a local port and listen to it. Any errors must be detected and the process must be aborted by returning a null pointer. Success will return a pointer to the server struct.

// void closeServer(Server *s);
// 	Frees all allocated memory of the Server struct and closes all of the sockets being used.

// int serverSendReceive(Server *s, void *buffer);
// 	This is the largest bulk of the Server’s work. Here it will receive incoming client connections and add them to clientSocks. When a client is added, the server will send them the welcomeMessage, which can be initialized to 0 or whatever value you want. 
// The server will also check for incoming data from its clients and send this to any other clients that are connected. If a client disconnects it should be removed from clientSocks. 
// 	Here it will be useful to use FD_SETS and select() to keep track of connections. Remember we want this to be non-blocking!
// 	The return value is how many bytes were read by the server.


Server* setUpServerConnection() {
    Server *s = (Server *)calloc(sizeof(Server), 1);
    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    s->maxClients = 10;
    s->clientSocks = (int *)calloc(sizeof(int), s->maxClients);
    s->addrlen = sizeof(s->addr);
    s->addr.sin_addr.s_addr = INADDR_ANY;
    s->addr.sin_family = AF_INET;
    s->addr.sin_port = htons(8080);
    s->tv.tv_sec = 0;
    s->tv.tv_usec = 0;
    bind(s->sock, (struct sockaddr *)&s->addr, s->addrlen);
    listen(s->sock, 0);
    return s;
}

void closeServer(Server *s) {
    if (s != NULL) {
        if (s->clientSocks != NULL) {
            for (int i = 0; i < s->maxClients; i++) {
                if (s->clientSocks[i] != 0) {
                    close(s->clientSocks[i]);
                }
            }
            free(s->clientSocks);
        }
        close(s->sock);
        free(s);
    }
}

int serverSendReceive(Server *s, void *buffer) {
    int activity = 0;
    int res = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(s->sock, &readfds);
    for (int i = 0; i < s->maxClients; i++) {
        if (s->clientSocks[i] != 0) {
            FD_SET(s->clientSocks[i], &readfds);
        }
    }
    activity = select(s->sock + 1, &readfds, NULL, NULL, NULL);
    if (activity >= 0) {
        if (FD_ISSET(s->sock, &readfds)) {
            int newSock = accept(s->sock, (struct sockaddr *)&s->addr, (socklen_t *)&s->addrlen);
            if (newSock < 0) {
                printf("accept failed\n");
                return (-1);
            }
            dprintf(newSock, welcomeMessage);
            for (int i = 0; i < s->maxClients; i++) {
                if (s->clientSocks[i] == 0) {
                    s->clientSocks[i] = newSock;
                    break;
                }
            }
        }
        for (int i = 0; i < s->maxClients; i++) {
            if (s->clientSocks[i] != 0 && FD_ISSET(s->clientSocks[i], &readfds)) {
                res = read(s->clientSocks[i], buffer, BUFF);
                if (res == 0) {
                    close(s->clientSocks[i]);
                    s->clientSocks[i] = 0;
                }
                for (int j = 0; j < s->maxClients; j++) {
                    if (s->clientSocks[j] != 0 && s->clientSocks[j] != s->clientSocks[i]) {
                        write(s->clientSocks[j], buffer, res);
                    }
                }
            }
        }
    }
    return (res);
}