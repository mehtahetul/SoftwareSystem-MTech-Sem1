/*
==========================================================================================================================
Name : 30_daemon.c
Author : Hetul Mehta
Description : C program to run a script after a delay using a daemon process.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SCRIPT_PATH "/home/hetul/Desktop/hands-on-1/30/script.sh"

int main() {

    pid_t pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    if (setsid() < 0)
        exit(EXIT_FAILURE);

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    sleep(30);

    system(SCRIPT_PATH);

    return 0;
}
/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/30$ cat /tmp/script_log.txt
Script is running at Fri Sep 18 11:30:04 AM IST 2026
Script is running at Fri Sep 18 11:36:38 AM IST 2026
==========================================================================================================================
*/
