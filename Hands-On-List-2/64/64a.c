
/*
============================================================================
Name        : 64a.c
Author      : Hetul Mehta
Description : Wait for SIGSTOP and determine whether it can be caught.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Caught signal %d\n", sig);
}

int main()
{
    FILE *fp = fopen("pid.txt", "w");

    if (fp == NULL)
    {
        perror("fopen");
        return 1;
    }

    fprintf(fp, "%d", getpid());
    fclose(fp);

    /*
       SIGSTOP cannot be caught. This registration does not
       install a working handler for SIGSTOP.
    */
    signal(SIGSTOP, handler);

    printf("Process PID: %d\n", getpid());
    printf("Waiting for SIGSTOP...\n");
    fflush(stdout);

    while (1)
    {
        pause();
    }

    return 0;
}

/*
============================================================================
Sample Output:
Process PID: 12345
Waiting for SIGSTOP...

After SIGSTOP is sent, the shell may show:
[1]+  Stopped                 ./64a
============================================================================
*/

