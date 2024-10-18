#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int number;
    char *message;
} thread_arg;

void *threadFunc(void *arg) {
    thread_arg *data = (thread_arg *)arg;
    printf("T: Number = %d, Message: %s\n", data->number, data->message);
    return NULL;
}

int main() {
    pthread_t thread;
    thread_arg *data = (thread_arg *)malloc(sizeof(thread_arg));
    data->number = 52;
    data->message = "Hello World!";

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&thread, &attr, threadFunc, data);


    pthread_attr_destroy(&attr);
    sleep(1);
    free(data);
    return 0;
}