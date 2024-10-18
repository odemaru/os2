#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

void *threadFunction(void *arg) {

    printf("T [%lu]: I`m newest threadd\n", pthread_self());
    return NULL;
}


int main(void) {
    pthread_t thread;
    while (1) {
        pthread_create(&thread, NULL, threadFunction, NULL);

        pthread_join(thread, NULL);
    }

    return 0;
}

