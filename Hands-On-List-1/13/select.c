/*
==========================================================================================================================
Name : 13_select.c
Author : Hetul Mehta
Description : C program to wait for STDIN for 10 seconds using select.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

int main(void)
{
    fd_set readfds;
    struct timeval timeout;
    int retval;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if(retval == -1)
    {
        perror("select");
        exit(EXIT_FAILURE);
    }
    else if(retval == 0)
    {
        printf("No data entered within 10 seconds.\n");
    }
    else
    {
        if(FD_ISSET(STDIN_FILENO, &readfds))
        {
            char buf[1024];

            ssize_t len = read(STDIN_FILENO, buf, sizeof(buf) - 1);

            if(len > 0)
            {
                buf[len] = '\0';
                printf("Data available: %s", buf);
            }
        }
    }

    return 0;
}


/*
==========================================================================================================================
Output : 
Waiting for input for 10 seconds...
Hello, my name is hetul
Data available: Hello, my name is hetul


Waiting for input for 10 seconds...
Hello, my name is hetul
Data available: Hello, my name is hetul

==========================================================================================================================
*/