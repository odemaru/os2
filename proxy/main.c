#include "proxy.h"
#include "cache.h"
#include "network.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void HandleClient(int clienSock) {
    char buffer[BUFFER_SIZE];
    char url[1024];

    int recieved = recv(clienSock, buffer, sizeof(buffer) - 1, 0);
    if (recieved < 0) {
        perror("recv");
        close(clienSock);
        return;
    }
    buffer[recieved] = '\0';

    sscanf(buffer, "GET %s HTTP/1.0", url);
    printf("%s\n", url);

    cache_entry_t *cacheEntry = FindInCache(url);
    if (cacheEntry != NULL) {
        send(clienSock, cacheEntry->url, sizeof(cacheEntry->responseSize), 0);
        close(clienSock);
        return;
    }

    int responseSize = SendRequest(url, buffer, BUFFER_SIZE);
    if (responseSize > 0) {
        addToCache(url, buffer, responseSize);
        send(clienSock, buffer, responseSize, 0);
    }

    close(clienSock);
}

void *clientHandler(void *arg) {
    int clienSock = *(int*)arg;
    free(arg);
    HandleClient(clienSock);
    return NULL;
}

int main() {
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(serverAddr);
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSock);
        exit(EXIT_FAILURE);
    }

    if (listen(serverSock, 10) < 0) {
        perror("listen");
        close(serverSock);
        exit(EXIT_FAILURE);
    }

    printf("Server Listening on port %d\n", PORT);

    while (1) {
        int clienSock = accept(serverSock, (struct sockaddr*)&clientAddr, &addrLen);
        if (clienSock < 0) {
            perror("accept");
            continue;
        }

        pthread_t clientThread;
        int *newSock = malloc(sizeof(int));
        *newSock = clienSock;
        if (pthread_create(&clientThread, NULL, clientHandler, newSock) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
            free(newSock);
        }
        pthread_detach(clientThread);

    }
    close(serverSock);
    return 0;
}
