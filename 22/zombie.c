/*
==========================================================================================================================
Name : 22_zombie.c
Author : Hetul Mehta
Description : C program to create a zombie process.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    if (fork() == 0) {
        // Child process finishes immediately
        printf("Child Process: PID = %d, Parent PID = %d\n",
               getpid(), getppid());
    }
    else {
        // Parent remains alive while child has finished
        printf("Parent Process ID: %d\n", getpid());
        sleep(25);
    }

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/22$ ./zombie 
Child Process: PID = 5642, Parent PID = 5641
Parent Process ID: 5641


hetul@hetul:~/Desktop/hands-on-1/22$ ps -o pid,ppid,state,cmd -p 5642
    PID    PPID S CMD
   5642    5641 Z [zombie] <defunct>
==========================================================================================================================
*/