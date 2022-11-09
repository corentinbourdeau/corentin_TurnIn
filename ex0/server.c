#include "server.h"

void *welcomeMessage;
int welcomeSize;
Server *s;

Server* setUpServerConnection() {
    Server *s = (Server *)calloc(sizeof(Server), 1);
    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    s->maxClients = 10;
    s->clientSocks = (int *)calloc(sizeof(int), s->maxClients);
    s->addrlen = sizeof(s->addr);
    int opt = 1;
    setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    s->addr.sin_addr.s_addr = INADDR_ANY;
    s->addr.sin_family = AF_INET;
    s->addr.sin_port = htons(8080);
    fcntl(s->sock, F_SETFL, O_NONBLOCK);
    s->tv.tv_sec = 0;
    s->tv.tv_usec = 0;
    bind(s->sock, (struct sockaddr *)&s->addr, sizeof(s->addr));
    listen(s->sock, 3);
    return s;
}

void closeServer(Server *s) {

    for (int i = 0; i < s->maxClients; i++) {
        if (s->clientSocks[i] != 0) {
            close(s->clientSocks[i]);
        }
    }
    close(s->sock);
    free(s->clientSocks);
    free(s);
}

void serverSendReceive(Server *s, void *buffer, int *gotData) {

    int new_sock;
    int addrlen = sizeof(s->addr);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(s->sock, &readfds);

    int max_sd = s->sock;
    int valread;

    for (int i = 0; i < s->maxClients; i++) {
        int sd = s->clientSocks[i];
        if (sd > 0) {
            FD_SET(sd, &readfds);
        }
        if (sd > max_sd) {
            max_sd = sd;
        }
    }
    int activity = select(max_sd + 1, &readfds, NULL, NULL, &s->tv);
    if (activity < 0 && (errno != EINTR)) {
        printf("Error selecting socket");
    }
    if (FD_ISSET(s->sock, &readfds)) {
        if ((new_sock = accept(s->sock, (struct sockaddr *)&s->addr, (socklen_t *)&addrlen)) < 0) {
            printf("accept failed\n");
        } else {
            printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_sock, inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
            for (int i = 0; i < s->maxClients; i++) {
                if (s->clientSocks[i] == 0) {
                    s->clientSocks[i] = new_sock;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
            if (send(new_sock, welcomeMessage, welcomeSize, 0) != welcomeSize) {
                printf("Error sending welcome message\n");
            }
            printf("Welcome message sent successfully\n");
            if (fcntl(new_sock, F_SETFL, O_NONBLOCK) < 0) {
                printf("Error setting socket to non-blocking\n");
            }
        }
    }
    for (int i = 0; i < s->maxClients; i++) {
        int sd = s->clientSocks[i];
        if (FD_ISSET(sd, &readfds)) {
            if ((valread = read(sd, buffer, BUFF)) == 0) {
                getpeername(sd, (struct sockaddr *)&s->addr, (socklen_t *)&addrlen);
                printf("Host disconnected, ip %s, port %d\n", inet_ntoa(s->addr.sin_addr), ntohs(s->addr.sin_port));
                close(sd);
                s->clientSocks[i] = 0;
            }
            else {
                printf("Message received from client %d: %i\n", i, *(int *)buffer);
                *gotData = valread;
                for (int i = 0; i < s->maxClients; i++) {
                    int sd2 = s->clientSocks[i];
                    if (sd2 > 0 && sd2 != sd) {
                        if (send(sd2, buffer, *gotData, 0) != *gotData) {
                            printf("Error sending message\n");
                        }
                    }
                }
            }
        }
    }
}