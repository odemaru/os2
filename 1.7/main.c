#include <stdio.h>
#include "uthread.h"

void *threadFunc(void *arg) {
    printf("runing....\n");
    return NULL;
}

int main() {
    uthread_t uthread;

    uthread_create(&uthread, threadFunc, NULL);
    uthread_join(&uthread);

    return 0;
}