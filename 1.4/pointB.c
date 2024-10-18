#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg) {
    int count = 0;
    while (1) {
        count++;
        pthread_testcancel(); //разкомментить чтобы работало))
    }
    return NULL;
}

int main() {
    pthread_t thread;

    pthread_create(&thread, NULL, threadFunction, NULL);
    sleep(1);

    pthread_cancel(thread);
    pthread_join(thread, NULL);
    return 0;
}