/*
==========================================================================================================================
Name : 24_waitpid.c
Author : Hetul Mehta
Description : C program to create three child processes and wait for a specific child using waitpid.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

    pid_t pid[3];

    for (int i = 0; i < 3; i++) {

        pid[i] = fork();

        if (pid[i] == 0) {
            printf("Child %d created with PID %d, parent PID %d\n",
                   i + 1, getpid(), getppid());

            sleep(2 + i);

            exit(0);
        }
    }

    int status;

    // Wait specifically for Child 2
    pid_t waited_pid = waitpid(pid[1], &status, 0);

    printf("Parent waited for child with PID %d (Child 2)\n",
           waited_pid);

    return 0;
}


/*
==========================================================================================================================
Child 1 created with PID 5768, parent PID 5767
Child 2 created with PID 5769, parent PID 5767
Child 3 created with PID 5770, parent PID 5767
Parent waited for child with PID 5769 (Child 2)
==========================================================================================================================
*/
