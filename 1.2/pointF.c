#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void *mythread(void *arg) {
    printf("Thread [%lu]: Hello, I'm a detached thread!\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;

    // Инициализация атрибутов потока
    pthread_attr_init(&attr);
    // Установка атрибута на detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while (1) {
        // Создание detached потока
        pthread_create(&thread, &attr, mythread, NULL);
        sleep(1);  // Чтобы не перегружать процессор
    }

    // Освобождение атрибутов
    pthread_attr_destroy(&attr);

    return 0;
}
