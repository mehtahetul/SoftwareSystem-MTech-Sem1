
/*
    Question 50: Deadlock
    Description: Develop a program that intentionally induces a deadlock scenario using semaphores.
    Author: Hetul Mehta
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem1, sem2;

void *thread1(void *arg)
{
    printf("Thread 1: Waiting for semaphore 1...\n");
    sem_wait(&sem1);
    printf("Thread 1: Acquired semaphore 1\n");

    sleep(1);

    printf("Thread 1: Waiting for semaphore 2...\n");
    sem_wait(&sem2);

    printf("Thread 1: Acquired semaphore 2\n");

    sem_post(&sem2);
    sem_post(&sem1);

    return NULL;
}

void *thread2(void *arg)
{
    printf("Thread 2: Waiting for semaphore 2...\n");
    sem_wait(&sem2);
    printf("Thread 2: Acquired semaphore 2\n");

    sleep(1);

    printf("Thread 2: Waiting for semaphore 1...\n");
    sem_wait(&sem1);

    printf("Thread 2: Acquired semaphore 1\n");

    sem_post(&sem1);
    sem_post(&sem2);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

/*
===================================================================================
SAMPLE OUTPUT:-
Thread 1: Waiting for semaphore 1...
Thread 1: Acquired semaphore 1
Thread 2: Waiting for semaphore 2...
Thread 2: Acquired semaphore 2
Thread 1: Waiting for semaphore 2...
Thread 2: Waiting for semaphore 1...


====================================================================================
*/


