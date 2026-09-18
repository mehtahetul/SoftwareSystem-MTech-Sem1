/*
==========================================================================================================================
Name : 20_fork.c
Author : Hetul Mehta
Description : C program to create a child process using fork and print parent and child process IDs.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    }
    else {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n",
               getpid(), pid);
    }

    return 0;
}

/*
==========================================================================================================================
Parent Process: PID = 5427, Child PID = 5428
Child Process: PID = 5428, Parent PID = 5427
==========================================================================================================================
*/
