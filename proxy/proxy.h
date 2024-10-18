#ifndef PROXY_H
#define PROXY_H

#include <stdio.h>

#define PORT 8080
#define BUFFER_SIZE 8192

void HandlerClient(int clientSock);

void *ClientHandler(void *arg);

typedef struct {
  char *url;
  char *response;
  size_t responseSize;
} cache_entry_t;

cache_entry_t *FindInCache(char *url);

void addToCache(char *url, char *response, size_t responseSize);
#endif
