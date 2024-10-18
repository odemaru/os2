#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("T: Hello World\n");
    return NULL;
}


int main(void) {
    pthread_t thread;

    pthread_create(&thread, NULL, threadFunction, NULL);

    pthread_join(thread, NULL);
    printf("M: all finished\n");
    return 0;
}
