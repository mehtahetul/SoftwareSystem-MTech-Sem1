
/*
============================================================================
Name        : 59e.c
Author      : Hetul Mehta
Description : Catch SIGALRM using setitimer and ITIMER_REAL.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigalrm_handler(int sig)
{
    printf("Signal caught %d\n", sig);
    printf("Exiting safely.\n");
    _exit(1);
}

int main()
{
    struct itimerval timer = {0};

    signal(SIGALRM, sigalrm_handler);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 500000;

    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL timer started.\n");
    fflush(stdout);

    while (1)
        pause();

    return 0;
}

/*
============================================================================
Sample Output:
ITIMER_REAL timer started.
Signal caught 14
Exiting safely.
============================================================================
*/

