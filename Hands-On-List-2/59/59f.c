
/*
============================================================================
Name        : 59f.c
Author      : Hetul Mehta
Description : Catch SIGVTALRM using setitimer and ITIMER_VIRTUAL.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigvtalrm_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    struct itimerval timer = {0};

    signal(SIGVTALRM, sigvtalrm_handler);

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 500000;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL timer started.\n");
    fflush(stdout);

    while (1)
    {
        /* Consume user-mode CPU time. */
    }

    return 0;
}

/*
============================================================================
Sample Output:
ITIMER_VIRTUAL timer started.
Signal caught 26
Exiting safely.
============================================================================
*/

