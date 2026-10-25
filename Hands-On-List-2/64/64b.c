
/*
============================================================================
Name        : 64b.c
Author      : Hetul Mehta
Description : Send SIGSTOP to another process using the kill system call.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("pid.txt", "r");

    if (fp == NULL)
    {
        perror("Could not open pid.txt");
        return 1;
    }

    int pid;

    if (fscanf(fp, "%d", &pid) != 1)
    {
        printf("Could not read PID\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    if (kill(pid, SIGSTOP) == -1)
    {
        perror("kill");
        return 1;
    }

    printf("SIGSTOP sent to process %d\n", pid);

    return 0;
}

/*
============================================================================
Sample Output:
SIGSTOP sent to process 12345
============================================================================
*/

