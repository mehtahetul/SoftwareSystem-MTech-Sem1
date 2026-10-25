
/*
============================================================================
Name        : 59c.c
Author      : Hetul Mehta
Description : Catch SIGFPE using the signal system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigfpe_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    signal(SIGFPE, sigfpe_handler);

    volatile int a = 5;
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
Exiting safely.
============================================================================
*/

