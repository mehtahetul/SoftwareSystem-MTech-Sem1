
/*
============================================================================
Name        : 58.c
Author      : Hetul Mehta
Description : Write a simple program to create three threads and print
              the IDs of the created threads.
============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d created. Thread ID: %lu\n",
           id, (unsigned long)pthread_self());

    sleep(id);

    printf("Thread %d has completed and is exiting\n", id);

    return NULL;
}

int main()
{
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&threads[i], NULL,
                           thread_function, &ids[i]) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

/*
============================================================================
Sample Output (thread IDs and order may vary):
Thread 1 created. Thread ID: 263854520201568
Thread 2 created. Thread ID: 263854511747424
Thread 3 created. Thread ID: 263854503293280
Thread 1 has completed and is exiting
Thread 2 has completed and is exiting
Thread 3 has completed and is exiting
============================================================================
*/

