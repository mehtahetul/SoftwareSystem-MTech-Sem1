/*
==========================================================================================================================
Name : 23_orphan.c
Author : Hetul Mehta
Description : C program to create an orphan process.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main(void) {

    if (fork() == 0) {

        // Child process
        printf("Before: Child PID = %d, Parent PID = %d\n",
               getpid(), getppid());

        sleep(3);

        // Parent has terminated by now
        printf("After: Child PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    }
    else {

        // Parent terminates before child
        sleep(1);

        printf("Parent Process ID: %d\n", getpid());
    }

    return 0;
}


/*
==========================================================================================================================
Before: Child PID = 5703, Parent PID = 5702
Parent Process ID: 5702
hetul@hetul:~/Desktop/hands-on-1/23$ After: Child PID = 5703, Parent PID = 2409
==========================================================================================================================
*/