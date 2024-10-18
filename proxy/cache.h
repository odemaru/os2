#ifndef CACHE_H
#define CACHE_H

#include "proxy.h"

#define CACHE_SIZE 1

cache_entry_t *findInCache(char *url);

void addToCache(char *url, char *response, size_t responseSize);
#endif