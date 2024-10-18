#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *threadFunction(void *arg) {
    char *message = "hello world";
    printf("T: return message\n");
    return (void*)message;
}


int main(void) {
    pthread_t thread;
    int *ret;

    pthread_create(&thread, NULL, threadFunction, NULL);

    pthread_join(thread, (void**)&ret);
    printf("M: all finished with returned %s\n", ret);

    return 0;
}

