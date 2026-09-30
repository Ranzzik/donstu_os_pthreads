#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int head = 0;
int tail = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 1; i <= 20; i++) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_not_full, &mutex);
        }
        buffer[tail] = i;
        tail = (tail + 1) % BUFFER_SIZE;
        count++;
        printf("Производитель добавил: %d (осталось в буфере: %d)\n", i, count);
        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(50000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 20; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&cond_not_empty, &mutex);
        }
        int val = buffer[head];
        head = (head + 1) % BUFFER_SIZE;
        count--;
        printf("Потребитель забрал : %d (осталось в буфере: %d)\n", val, count);
        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&mutex);
        usleep(80000);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
