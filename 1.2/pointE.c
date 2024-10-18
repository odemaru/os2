#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void *threadFunction(void *arg) {

    printf("T [%lu]: I`m newest threadd\n", pthread_self());
    pthread_detach(pthread_self()); //leave
    return NULL;
}


int main(void) {
    pthread_t thread;
    while (1) {
        pthread_create(&thread, NULL, threadFunction, NULL);

        //sleep(1);
    }

    return 0;
}

