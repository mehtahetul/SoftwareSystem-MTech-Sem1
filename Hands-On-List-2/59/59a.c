
/*
============================================================================
Name        : 59a.c
Author      : Hetul Mehta
Description : Catch SIGSEGV using the signal system call.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void segv_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("SIGSEGV action: exiting safely.\n");
    _exit(1);
}

int main()
{
    signal(SIGSEGV, segv_handler);

    printf("Triggering SIGSEGV by dereferencing NULL...\n");
    fflush(stdout);

    int *p = NULL;
    *p = 22;

    return 0;
}

/*
============================================================================
Sample Output:
Triggering SIGSEGV by dereferencing NULL...
Signal caught 11
SIGSEGV action: exiting safely.
============================================================================
*/

