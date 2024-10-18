#include <stdio.h>
#include <pthread.h>

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
    thread_arg data = {52, "Hello World!"};

    pthread_create(&thread, NULL, threadFunc, &data);
    pthread_join(thread, NULL);
    return 0;
}