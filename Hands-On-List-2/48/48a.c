
/*
==========================================================================================================================
Name : 48a.c
Author : Hetul Mehta
Description : Semaphore Creation and Initialization: Write a program to create a semaphore
and initialize its value: Create a binary semaphore.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = 1234;  // Key used to identify the binary semaphore

    // Create or access a semaphore set containing one semaphore
    int binary_sem = semget(key, 1, 0666 | IPC_CREAT);

    if (binary_sem == -1) {
        perror("Binary semget failed");
        exit(1);
    }

    // Initialize the semaphore value to 1 (available)
    if (semctl(binary_sem, 0, SETVAL, 1) == -1) {
        perror("Binary semctl failed");
        exit(1);
    }

    // Display the semaphore ID
    printf("Binary semaphore ID: %d\n", binary_sem);

    return 0;
}

/*
==========================================================================================================================
Output :
Binary semaphore ID: 1

==========================================================================================================================
*/

