#ifndef MTHREAD_H
#define MTHREAD_H

#include <sys/types.h>

typedef pid_t Mthread_t;

int Mthread_create(Mthread_t *thread, void *(*start_routine)(void *), void *arg);

#endif
// MTHREAD_H