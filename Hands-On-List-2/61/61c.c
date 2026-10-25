
/*
============================================================================
Name        : 61c.c
Author      : Hetul Mehta
Description : Catch SIGFPE using the sigaction system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigfpe_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("SIGFPE caught. Exiting safely.\n");
    fflush(stdout);
    _exit(1);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = sigfpe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    volatile int a = 10;
    volatile int b = 0;

    printf("Triggering SIGFPE...\n");
    fflush(stdout);

    int result = a / b;

    printf("Result: %d\n", result);

    return 0;
}

/*
============================================================================
Sample Output:
Triggering SIGFPE...
Signal caught 8
SIGFPE caught. Exiting safely.
============================================================================
*/

