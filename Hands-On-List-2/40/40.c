
/*
==========================================================================================================================
Name : 40.c
Author : Hetul Mehta
Description : Process File Limit and Pipe Size: Write a program to print the maximum number of
files that can be opened within a process and the size of a pipe (circular buffer).
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

int main() {
    // Get and display the maximum number of open file descriptors for this process
    printf("Maximum files that can be opened: %ld\n", sysconf(_SC_OPEN_MAX));

    int pipefd[2];  // File descriptors for the pipe

    pipe(pipefd);  // Create a pipe

    // Get and display the pipe's atomic-write limit in bytes
    printf("Pipe buffer size: %ld\n", fpathconf(pipefd[0], _PC_PIPE_BUF));

    // Close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

/*
==========================================================================================================================
Output :
Maximum files that can be opened: 1024
Pipe buffer size: 4096

==========================================================================================================================
*/

