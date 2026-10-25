
/*
============================================================================
Name        : 61b.c
Author      : Hetul Mehta
Description : Catch SIGINT using the sigaction system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int sig)
{
    printf("\nSignal caught %d\n", sig);
    printf("SIGINT caught. Exiting safely.\n");
    fflush(stdout);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT.\n");
    fflush(stdout);

    while (1)
    {
        pause();
    }

    return 0;
}

/*
============================================================================
Sample Output:
Press Ctrl+C to trigger SIGINT.
^C
Signal caught 2
SIGINT caught. Exiting safely.
============================================================================
*/

