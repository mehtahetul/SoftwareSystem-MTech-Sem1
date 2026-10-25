
/*
==========================================================================================================================
Name : 48b.c
Author : Hetul Mehta
Description : Semaphore Creation and Initialization: Write a program to create a semaphore
and initialize its value: Create a counting semaphore.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = 5678;  // Key used to identify the counting semaphore set

    // Create or access a set containing three semaphores
    int count_sem = semget(key, 3, 0666 | IPC_CREAT);

    if (count_sem == -1) {
        perror("Counting semget failed");
        exit(1);
    }

    // Initial values for the three semaphores
    int values[3] = {5, 3, 7};

    // Initialize each semaphore in the set
    for (int i = 0; i < 3; i++) {
        if (semctl(count_sem, i, SETVAL, values[i]) == -1) {
            perror("Counting semctl failed");
            exit(1);
        }
    }

    // Display the semaphore set ID
    printf("Counting semaphore ID: %d\n", count_sem);

    return 0;
}

/*
==========================================================================================================================
Output :
Counting semaphore ID: 2

==========================================================================================================================
*/

