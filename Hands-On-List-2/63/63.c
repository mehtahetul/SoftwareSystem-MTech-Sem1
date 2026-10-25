
/*
============================================================================
Name        : 63.c
Author      : Hetul Mehta
Description : Create an orphan process by sending SIGKILL from the child
              process to the parent using the kill system call.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        /* Child process */
        pid_t ppid = getppid();

        printf("Child process PID: %d\n", (int)getpid());
        printf("Parent PID before termination: %d\n", (int)ppid);
        fflush(stdout);

        /* Send SIGKILL to the parent process. */
        if (kill(ppid, SIGKILL) == -1)
        {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        sleep(2);

        printf("Child process PID: %d\n", (int)getpid());
        printf("New parent PID: %d\n", (int)getppid());

        exit(EXIT_SUCCESS);
    }
    else
    {
        /* Parent process */
        printf("Parent process PID: %d\n", (int)getpid());
        fflush(stdout);

        /* Remain alive until the child sends SIGKILL. */
        while (1)
            pause();
    }

    return 0;
}

/*
============================================================================
Sample Output (PIDs vary):
Parent process PID: 7698
Child process PID: 7699
Parent PID before termination: 7698
Child process PID: 7699
New parent PID: 2188
============================================================================
*/

