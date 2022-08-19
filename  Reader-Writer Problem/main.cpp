#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define buffersize 10
using  namespace std;
sem_t wrt;
pthread_mutex_t mutex;

int buffer[buffersize] = {1,2,3,4,5,6,7,8,9,10};
int numreader = 0;
void printBuffer()
{
    cout << "Printing Buffer  elements:"<< endl;
    for (int i = 0; i < buffersize; i++)
    {
        cout<<buffer[i]<<" ";
    }
    cout<<endl;
}
void *writer(void *args)
{
    int id = *(int*)args;
    sleep(id);
    cout<<endl<<"Writer "<<id<<":Waiting  "<<endl;
    sem_wait(&wrt);
    buffer[id % buffersize]= rand() % (100);
    buffer[(id % buffersize)+1]= rand() % (200)+15;
    cout<<endl<<"Writer "<<id<<":writes in the system"<<buffer[id % buffersize]<<","<<buffer[(id % buffersize)+1]<<endl;
    printBuffer();
    sem_post(&wrt);
    cout<<endl<<"Writer "<<id<<": Leaves  "<<endl;
}
void *reader(void *args)
{
    int id = *(int*)args;
    sleep(id);
    cout<<endl<<"Reader "<<id<<": Waiting  "<<endl;
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    cout<<endl<<"Reader "<<id<<": is Reading "<< buffer[id % buffersize]<<endl;
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    cout<<endl<<"Reader "<<id<<": Leaves  "<<endl;
}

int main()
{
    srand(time(NULL));
    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    while (1){
        for(int i = 0; i < 10; i++) {
            int* a = (int*)malloc(sizeof(int));
            *a = i;
            pthread_create(&read[i], NULL, &reader, a);
        }
        for(int i = 0; i < 5; i++) {
            int* a = (int*)malloc(sizeof(int));
            *a = i;
            pthread_create(&write[i], NULL, &writer, a);
        }

        for(int i = 0; i < 10; i++) {
            pthread_join(read[i], NULL);
        }
        for(int i = 0; i < 10; i++) {
            pthread_join(write[i], NULL);
        }

    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;

}