
/*
============================================================================
Name        : 60.c
Author      : Hetul Mehta
Description : Write a program to ignore SIGINT and then reset it to the
              default action using the signal system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    signal(SIGINT, SIG_IGN);

    printf("CTRL+C will not terminate the program for the next 5 seconds.\n");
    fflush(stdout);

    sleep(5);

    signal(SIGINT, SIG_DFL);

    printf("\nTry pressing CTRL+C now.\n");
    fflush(stdout);

    sleep(5);

    return 0;
}

/*
============================================================================
Sample Output:
CTRL+C will not terminate the program for the next 5 seconds.
^C
Try pressing CTRL+C now.
^C

============================================================================
*/

