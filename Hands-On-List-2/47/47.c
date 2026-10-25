
/*
==========================================================================================================================
Name : 47.c
Author : Hetul Mehta
Description : Shared Memory Operations: Write a program to create shared memory and
perform the following operations:
a. Write some data to the shared memory
b. Attach with O_RDONLY and check whether you are able to overwrite
c. Detach the shared memory
d. Remove the shared memory
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Generate a key using shmfile and project identifier 65
    key_t key = ftok("shmfile", 65);

    // Create or access a shared memory segment of 1024 bytes
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory with read and write permissions
    char *data = (char *) shmat(shmid, NULL, 0);

    // Write data into the shared memory
    strcpy(data, "Hello Shared Memory");
    printf("Data written: %s\n", data);

    // Attach the same shared memory in read-only mode
    char *read_only = (char *) shmat(shmid, NULL, SHM_RDONLY);

    // Display the data through the read-only attachment
    printf("Data read-only: %s\n", read_only);

    // Attempt to overwrite data through the read-only attachment
    // This will normally cause a segmentation fault on Linux
    strcpy(read_only, "Test");

    // This statement will normally not execute because of the segmentation fault
    printf("After overwrite attempt: %s\n", read_only);

    // Detach the writable attachment
    shmdt(data);

    // Detach the read-only attachment
    shmdt(read_only);

    // Mark the shared memory segment for removal
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

/*
==========================================================================================================================
Output :
Data written: Hello Shared Memory
Data read-only: Hello Shared Memory
Segmentation fault (core dumped)
==========================================================================================================================
*/

