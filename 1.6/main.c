#include <stdio.h>
#include <stdlib.h>
#include "Mthread.h"

void *threadFunc(void *arg) {
    printf("runnnnnnn\n");
    return NULL;
}

int main() {
    Mthread_t thread;

    Mthread_create(&thread, threadFunc, NULL);
    return 0;
}