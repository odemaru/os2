#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include "network.h"

int SendRequest(char *url, char *buffer, size_t bufferSize) {
    struct addrinfo hints, *res;
    int sockfg;
    char host[256], path[1024] = {"/"};
    char request[1024];

    sscanf(url, "http://%99[^/]%199[^/n]", host, path);
    printf("CONNECT TO HOST %s\n", host);
    printf("AND PATH %s\n", path);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, "80", &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    sockfg = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfg == -1) {
        perror("socket");
        return -1;
    }
    if (connect(sockfg, res->ai_addr, res->ai_addrlen) == -1) {
        close(sockfg);
        perror("connect");
        return -1;
    }

    sprintf(request, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", path, host);
    if (send(sockfg, request, strlen(request), 0) == -1) {
        perror("send");
        return -1;
    }

    int totalReceived = 0;
    int receieved;
    while ((receieved = recv(sockfg, buffer + totalReceived, bufferSize - totalReceived, 0)) > 0) {
        totalReceived += receieved;
    }

    if (receieved == -1) {
        perror("recv");
        return -1;
    }

    close(sockfg);
    freeaddrinfo(res);
    return totalReceived;

}