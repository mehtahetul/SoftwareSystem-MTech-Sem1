
/*
============================================================================
Name        : 59g.c
Author      : Hetul Mehta
Description : Catch SIGPROF using setitimer and ITIMER_PROF.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigprof_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    struct itimerval timer = {0};

    signal(SIGPROF, sigprof_handler);

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 500000;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF timer started.\n");
    fflush(stdout);

    while (1)
    {
        /* Consume CPU time. */
    }

    return 0;
}

/*
============================================================================
Sample Output:
ITIMER_PROF timer started.
Signal caught 27
Exiting safely.
============================================================================
*/

