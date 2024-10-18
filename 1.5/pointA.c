#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>


void sigint_handler(int sig) {
    printf("SIGINT received!\n");
}


void *threadSigintHandler(void *arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);


    pthread_sigmask(SIG_UNBLOCK, &set, NULL);


    signal(SIGINT, sigint_handler);
    printf("SIGINT handler...\n");


    while (1) {
        sleep(1);
    }
    return NULL;
}


void *threadSigquitWaiter(void *arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);

    int sig;
    printf("SIGQUIT waiter...\n");
    sigwait(&set, &sig);
    printf("SIGQUIT received!\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    sigset_t set;


    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);


    pthread_create(&thread1, NULL, threadSigintHandler, NULL);
    pthread_create(&thread2, NULL, threadSigquitWaiter, NULL);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
