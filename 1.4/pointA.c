#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *threadFunc(void *arg) {
    while (1) {
        printf("T: I`m working AAAAAAAAAA...\n");
        //sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunc, NULL);
    sleep(5);

    pthread_cancel(thread);
    pthread_join(thread, NULL);
    printf("M: thread is deaddd\n");
    return 0;
}