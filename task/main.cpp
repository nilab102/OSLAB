#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 10

pthread_mutex_t mutexBuffer;
sem_t semEmpty;
sem_t semFull;

int buffer[10];
int count = 0;

void* producer(void* args) {
    while (1) {
        int index = *(int*)args;
        int x = rand() % 100;
        sleep(2);
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        printf("producer Id %d: Data %d is inserted in the buffer\nEmpty space : n - %d \nFull space %d\n",index, x,count,count);
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}
void* consumer(void* args) {
    while (1) {

        int y;
        int index = *(int*)args;
        sleep(4);
        // Remove from the buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
        printf("consumer Id %d : Consumed Data %d From the buffer\nFull space %d\n",index , y,count,count);
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
        int* index = (int*)malloc(sizeof(int));
        *index = i;
        if (i%2==0) {
            pthread_create(&th[i], NULL, &producer, index) ;
            //perror("Failed to create thread");
        }
        else {
            pthread_create(&th[i], NULL, &consumer, index) ;
            //perror("Failed to create thread");
        }

    }
    for (i = 0; i < THREAD_NUM; i++) {
        pthread_join(th[i], NULL) ;
        //perror("Failed to join thread");

    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}



