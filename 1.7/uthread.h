#ifndef UTHREAD_H
#define UTHREAD_H

typedef struct {
  void *(*start_routine)(void *);
  void *arg;
} uthread_t;

int uthread_create(uthread_t *uthread, void *(*start_routine)(void *), void *arg);

void uthread_join(uthread_t *uthread);

#endif