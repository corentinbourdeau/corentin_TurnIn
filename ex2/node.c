#include "node.h"

void runNode(void (*processData)(void*, bool), void (*welcome)(void), void (*parse)(char*), char *ip) {
    pthread_t serverThread;
    pthread_t clientThread;
    pthread_create(&serverThread, NULL, runServer, processData);
    if (ip != 0) {
        pthread_create(&clientThread, NULL, runClient, ip);
    }
    welcome();
    char buff[1024];
    while (1) {
        fgets(buff, 1024, stdin);
        parse(buff);
    }
}

void *runServer(void *buff) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff));
    }
}

void *runClient(void *buff) {
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr;

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, buff, &serv_addr.sin_addr)<=0) {
        printf("\n inet_pton error occured");
        return 1;
    } else {
        printf("inet_pton success");
    }
}

void processString(void* buff, bool onServer) {
    if (onServer) {
        printf("Server: %s", buff);
    } else {
        printf("Client: %s", buff);
    }
}

void sendInput(char *buff) {
}

void welcomeText() {
    printf("Welcome to the node!\n");
}