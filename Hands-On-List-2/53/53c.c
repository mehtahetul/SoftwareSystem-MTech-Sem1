
/*
============================================================================
Name        : 53c.c
Author      : Hetul Mehta
Description : Set an interval timer using ITIMER_PROF for 10 seconds
              and 10 microseconds.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum)
{
    printf("Timer has expired, signal number is %d\n", signum);
}

int main()
{
    struct itimerval timer;

    signal(SIGPROF, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1)
    {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_PROF started. Waiting for SIGPROF...\n");

    while (1)
        pause();

    return 0;
}

/*
============================================================================
Sample Output:
ITIMER_PROF started. Waiting for SIGPROF...
============================================================================
*/

