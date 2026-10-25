
/*
============================================================================
Name : 49.c
Author : Hetul Mehta
Description : Semaphore Implementation: Write a program to implement a semaphore to
protect any critical section:
a. Rewrite the ticket number creation program using a semaphore
b. Protect shared memory from concurrent write access
c. Protect multiple pseudo resources (maybe two) using a counting semaphore
d. Remove the created semaphore
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

// Define union semun for semaphore control operations
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Decrease the semaphore value to enter the critical section
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};
    semop(semid, &sb, 1);
}

// Increase the semaphore value to leave the critical section
void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};
    semop(semid, &sb, 1);
}

int main() {
    // Generate a key using semfile and project identifier 65
    key_t key = ftok("semfile", 65);

    // Create or access a semaphore set containing one semaphore
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    union semun u;

    int choice;

    // Display the menu
    printf("\nSemaphore Demo Menu\n");
    printf("1. Ticket number creation (binary)\n");
    printf("2. Protect shared memory writes\n");
    printf("3. Protect 2 resources (counting)\n");
    printf("4. Remove semaphore\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // (a) Use a binary semaphore to protect ticket number creation

        u.val = 1;  // Initialize semaphore to 1 (unlocked)
        semctl(semid, 0, SETVAL, u);

        // Create or access shared memory for the ticket counter
        int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);

        // Attach shared memory to the process
        int *ticket = (int *) shmat(shmid, NULL, 0);

        // Generate three ticket numbers
        for (int i = 0; i < 3; i++) {
            sem_wait(semid);  // Enter critical section

            (*ticket)++;  // Increment the shared ticket counter

            printf("Process %d got ticket #%d\n", getpid(), *ticket);

            sem_signal(semid);  // Leave critical section

            sleep(1);
        }

        // Detach shared memory
        shmdt(ticket);
    }

    else if (choice == 2) {
        // (b) Use a binary semaphore to protect shared memory writes

        u.val = 1;  // Initialize semaphore to 1 (unlocked)
        semctl(semid, 0, SETVAL, u);

        // Create or access a shared memory segment of 1024 bytes
        int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

        // Attach shared memory
        char *str = (char *) shmat(shmid, NULL, 0);

        // Write to shared memory three times
        for (int i = 0; i < 3; i++) {
            sem_wait(semid);  // Enter critical section

            sprintf(str, "Process %d writing %d", getpid(), i);

            printf("Written: %s\n", str);

            sem_signal(semid);  // Leave critical section

            sleep(1);
        }

        // Detach shared memory
        shmdt(str);
    }

    else if (choice == 3) {
        // (c) Use a counting semaphore to manage two pseudo resources

        u.val = 2;  // Initialize the semaphore count to 2
        semctl(semid, 0, SETVAL, u);

        for (int i = 0; i < 2; i++) {
            sem_wait(semid);  // Acquire one available resource

            printf("Process %d acquired a resource...\n", getpid());

            sleep(2);  // Simulate using the resource

            printf("Process %d released resource\n", getpid());

            sem_signal(semid);  // Release the resource

            sleep(1);
        }
    }

    else if (choice == 4) {
        // (d) Remove the semaphore set
        semctl(semid, 0, IPC_RMID);

        printf("Semaphore removed.\n");
    }

    else {
        printf("Invalid choice\n");
    }

    return 0;
}

/*
===================================================================================
SAMPLE OUTPUT:

Semaphore Demo Menu
1. Ticket number creation (binary)
2. Protect shared memory writes
3. Protect 2 resources (counting)
4. Remove semaphore
Enter choice: 1
Process 5856 got ticket #1
Process 5856 got ticket #2
Process 5856 got ticket #4

Semaphore Demo Menu
1. Ticket number creation (binary)
2. Protect shared memory writes
3. Protect 2 resources (counting)
4. Remove semaphore
Enter choice: 1
Process 5859 got ticket #3
Process 5859 got ticket #5
Process 5859 got ticket #6
===================================================================================
*/

