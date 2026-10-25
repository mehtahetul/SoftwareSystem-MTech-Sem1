
/*
============================================================================
Name        : 59b.c
Author      : Hetul Mehta
Description : Catch SIGINT using the signal system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig)
{
    printf("\nSignal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    signal(SIGINT, sigint_handler);

    while (1)
    {
        printf("Press Ctrl+C to stop\n");
        fflush(stdout);
        sleep(1);
    }

    return 0;
}

/*
============================================================================
Sample Output:
Press Ctrl+C to stop
Press Ctrl+C to stop
^C
Signal caught 2
Exiting safely.
============================================================================
*/

