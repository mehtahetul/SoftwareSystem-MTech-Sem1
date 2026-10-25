
/*
============================================================================
Name        : 59d.c
Author      : Hetul Mehta
Description : Catch SIGALRM using the alarm system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigalrm_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    signal(SIGALRM, sigalrm_handler);

    printf("Setting alarm for 5 seconds...\n");
    fflush(stdout);

    alarm(5);

    while (1)
        pause();

    return 0;
}

/*
============================================================================
Sample Output:
Setting alarm for 5 seconds...
Signal caught 14
Exiting safely.
============================================================================
*/

