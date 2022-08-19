#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

void* producer(void* args) {
    while (1) {
        // Produce
        int id = *(int*)args;
        int x = rand() % 100;

        sleep(id+1);
        // Add to the buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        /*int semVal;
        sem_getvalue(&semFull, &semVal);*/
        printf("producer Id %d: Data %d is inserted in the buffer\nEmpty space : n - %d \nFull space %d\n",id, x,count,count);
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}
void* consumer(void* args) {
    while (1) {

        int y;
        int id = *(int*)args;
        sleep(id+10);
        // Remove from the buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
        printf("consumer Id %d : Consumed Data %d From the buffer\nEmpty space : n - %d \nFull space %d\n",id %(THREAD_NUM/2), y,count,count);
        // Consume
    }
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        int* a = (int*)malloc(sizeof(int));
        *a = i;
        if (i>THREAD_NUM/2) {
            if (pthread_create(&th[i], NULL, &producer, a) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, a) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}



