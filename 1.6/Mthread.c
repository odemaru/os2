#define _GNU_SOURCE
#include "Mthread.h"
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define STACK_SIZE (1024*1024)

static int threadStart(void *arg) {
    void **args = (void **)arg;
    void *(*start_routine)(void *) = args[0];
    void *routineArg = args[1];

    start_routine(routineArg);
    return 0;
}


int Mthread_create(Mthread_t *thread, void *(*start_routine)(void *), void *arg) {
    void *stack = malloc(STACK_SIZE);
    if (!stack) {
        return -1;
    }

    void *args[2] = {start_routine, arg};
    int flags = CLONE_FS | CLONE_VM | SIGCHLD | CLONE_FILES | CLONE_SIGHAND;

    *thread = clone(threadStart, stack + STACK_SIZE, flags, args);
    if (*thread == -1) {
        free(stack);
        return -1;
    }
    return 0;
}