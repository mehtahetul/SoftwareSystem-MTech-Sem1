
/*
==========================================================================================================================
Name : 34b.c
Author : Hetul Mehta
Description : Executing ls -l | wc: Write a program to execute ls -l | wc using dup2.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];  // File descriptors for the pipe

    pipe(fd);  // Create a pipe

    if (fork() == 0) {
        // First child process: executes ls -l

        close(fd[0]);  // Close the read end of the pipe

        // Redirect standard output (1) to the write end of the pipe
        dup2(fd[1], 1);

        close(fd[1]);  // Close the original write descriptor

        // Execute ls -l; its output goes into the pipe
        execlp("ls", "ls", "-l", NULL);
    } else {
        if (fork() == 0) {
            // Second child process: executes wc

            close(fd[1]);  // Close the write end of the pipe

            // Redirect standard input (0) to the read end of the pipe
            dup2(fd[0], 0);

            close(fd[0]);  // Close the original read descriptor

            // Execute wc; it reads input from the pipe
            execlp("wc", "wc", NULL);
        } else {
            // Parent process

            close(fd[0]);  // Close the read end
            close(fd[1]);  // Close the write end

            wait(NULL);  // Wait for the first child to finish
            wait(NULL);  // Wait for the second child to finish
        }
    }

    return 0;
}

/*
==========================================================================================================================
Output :
      5      38     215
==========================================================================================================================
*/

