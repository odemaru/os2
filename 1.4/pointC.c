#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


void clean(void *arg) {
    free(arg);
    printf("C: Done cleaning!\n");
}

void *threadFunc(void *arg) {
    char *message = malloc(20);
    strcpy(message, "Hello World!");
    pthread_cleanup_push(clean, message);

    while (1) {
        printf("%s\n", message);
        sleep(1);
        pthread_testcancel();
    }

    pthread_cleanup_pop(1);
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunc, NULL);
    sleep(5);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
    printf("M: Canceled that thread!\n");
    return 0;
}
