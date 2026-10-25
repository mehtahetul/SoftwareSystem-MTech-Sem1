
/*
============================================================================
Name        : 61a.c
Author      : Hetul Mehta
Description : Catch SIGSEGV using the sigaction system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigsegv_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("SIGSEGV caught. Exiting safely.\n");
    fflush(stdout);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGSEGV, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("Triggering SIGSEGV...\n");
    fflush(stdout);

    int *p = NULL;
    *p = 10;

    return 0;
}

/*
============================================================================
Sample Output:
Triggering SIGSEGV...
Signal caught 11
SIGSEGV caught. Exiting safely.
============================================================================
*/

