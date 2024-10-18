#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "cache.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //ура мутекс
cache_entry_t cache[CACHE_SIZE];
int cacheCount = 0;

cache_entry_t *FindInCache(char *url) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < cacheCount; i++) {
        if (strcmp(url, cache[i].url) == 0) {
            pthread_mutex_unlock(&mutex);
            return &cache[i];
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void addToCache(char *url, char *response, size_t responseSize) {
    pthread_mutex_lock(&mutex);
    if (cacheCount < CACHE_SIZE) {
        cache[cacheCount].url = strdup(url);
        cache[cacheCount].response = malloc(responseSize);
        memcpy(cache[cacheCount].response, response, responseSize);
        cache[cacheCount].responseSize = responseSize;
        cacheCount++;
    } else {
        //LRU алгос
        printf("DROPPED THIS %s\n ", cache[0].url);
        free(cache[0].url);
        free(cache[0].response);
        for (int i = 1; i < CACHE_SIZE; i++) {
            cache[i - 1] = cache[i];
        }
        cache[CACHE_SIZE - 1].url = strdup(url);
        cache[CACHE_SIZE - 1].response = malloc(responseSize);
        memcpy(cache[CACHE_SIZE - 1].response, response, responseSize);
        cache[CACHE_SIZE - 1].responseSize = responseSize;
    }
    pthread_mutex_unlock(&mutex);
}