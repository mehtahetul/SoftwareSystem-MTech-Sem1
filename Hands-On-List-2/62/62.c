
/*
============================================================================
Name        : 62.c
Author      : Hetul Mehta
Description : Ignore SIGINT and then reset it to the default action
              using the sigaction system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    struct sigaction sa;

    /* Ignore SIGINT. */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("CTRL+C will not terminate the program for the next 5 seconds.\n");
    fflush(stdout);

    sleep(5);

    /* Restore the default action for SIGINT. */
    sa.sa_handler = SIG_DFL;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("\nTry pressing CTRL+C now.\n");
    fflush(stdout);

    sleep(5);

    return 0;
}

/*
============================================================================
Sample Output:
CTRL+C will not terminate the program for the next 5 seconds.
^C^C^C
Try pressing CTRL+C now.
============================================================================
*/

