#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *threadFunction(void *arg) {
    int *result = malloc(sizeof(int));
    *result = 52;
    printf("T: return 52\n");
    return (void*)result;
}


int main(void) {
    pthread_t thread;
    int *ret;

    pthread_create(&thread, NULL, threadFunction, NULL);
    pthread_create(&thread,

    pthread_join(thread, (void**)&ret);
    printf("M: all finished with returned %d\n", *ret);
    free(ret);
    return 0;
}

