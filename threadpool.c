#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "threadpool.h"

#define NUMBER_OF_THREADS 3
#define QUEUE_SIZE 10

typedef struct
{
    void (*function)(void *);
    void *data;
} task;

/* Queue */
task work_queue[QUEUE_SIZE];

int queue_front = 0;
int queue_rear = 0;
int queue_size = 0;

/* Synchronization */
pthread_mutex_t mutex;
sem_t tasks;

/* Worker threads */
pthread_t workers[NUMBER_OF_THREADS];

void *worker(void *param)
{
    while (1)
    {
        sem_wait(&tasks);

        pthread_mutex_lock(&mutex);

        if (queue_size > 0)
        {
            task current = work_queue[queue_front];

            queue_front = (queue_front + 1) % QUEUE_SIZE;
            queue_size--;

            pthread_mutex_unlock(&mutex);

            current.function(current.data);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

void pool_init(void)
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&tasks, 0, 0);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_create(&workers[i], NULL, worker, NULL);
    }

    printf("Thread pool initialized.\n");
}

int pool_submit(void (*somefunction)(void *), void *p)
{
    pthread_mutex_lock(&mutex);

    if (queue_size == QUEUE_SIZE)
    {
        pthread_mutex_unlock(&mutex);
        return 1;
    }

    work_queue[queue_rear].function = somefunction;
    work_queue[queue_rear].data = p;

    queue_rear = (queue_rear + 1) % QUEUE_SIZE;
    queue_size++;

    pthread_mutex_unlock(&mutex);

    sem_post(&tasks);

    return 0;
}

void pool_shutdown(void)
{
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_cancel(workers[i]);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(workers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&tasks);

    printf("Thread pool shutdown complete.\n");
}