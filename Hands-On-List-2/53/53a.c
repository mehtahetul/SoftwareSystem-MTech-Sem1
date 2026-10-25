
/*
============================================================================
Name        : 53a.c
Author      : Hetul Mehta
Description : Set an interval timer using ITIMER_REAL for 10 seconds
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

    signal(SIGALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("ITIMER_REAL started. Waiting for SIGALRM...\n");

    while (1)
        pause();

    return 0;
}

/*
============================================================================
Sample Output:
ITIMER_REAL started. Waiting for SIGALRM...
Timer has expired, signal number is 14
Timer has expired, signal number is 14
============================================================================
*/

