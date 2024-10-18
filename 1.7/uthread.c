#include <stdio.h>
#include <stdlib.h>
#include "uthread.h"

int uthread_create(uthread_t *uthread, void *(*start_routine)(void *), void *arg) {
    if (!uthread || !start_routine) {
        return -1;
    }

    uthread->start_routine = start_routine;
    uthread->arg = arg;
    return 0;
}

void uthread_join(uthread_t *uthread) {
    if (uthread && uthread->start_routine) {
        uthread->start_routine(uthread->arg);
    }
}