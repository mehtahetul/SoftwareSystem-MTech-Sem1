
/*
==========================================================================================================================
Name : 35.c
Author : Hetul Mehta
Description : Counting Directories with dup2: Write a program to find the total number of
directories in the present working directory using ls -l | grep ^d | wc. Implement the
solution using only dup2.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];  // fd1 connects ls to grep; fd2 connects grep to wc

    pipe(fd1);  // Create pipe between ls and grep
    pipe(fd2);  // Create pipe between grep and wc

    if (fork() == 0) {
        // First child process: executes ls -l

        close(fd1[0]);  // Close the read end of the first pipe
        close(fd2[0]);  // Close both ends of the second pipe
        close(fd2[1]);

        // Redirect standard output to the write end of fd1
        dup2(fd1[1], 1);

        close(fd1[1]);  // Close the original write descriptor

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
    } else {
        if (fork() == 0) {
            // Second child process: executes grep ^d

            close(fd1[1]);  // Close the write end of the first pipe
            close(fd2[0]);  // Close the read end of the second pipe

            // Redirect standard input to the read end of fd1
            dup2(fd1[0], 0);

            // Redirect standard output to the write end of fd2
            dup2(fd2[1], 1);

            close(fd1[0]);  // Close the original read descriptor
            close(fd2[1]);  // Close the original write descriptor

            // Execute grep ^d to select directory entries
            execlp("grep", "grep", "^d", NULL);
        } else {
            if (fork() == 0) {
                // Third child process: executes wc -l

                close(fd1[0]);  // Close both ends of the first pipe
                close(fd1[1]);

                close(fd2[1]);  // Close the write end of the second pipe

                // Redirect standard input to the read end of fd2
                dup2(fd2[0], 0);

                close(fd2[0]);  // Close the original read descriptor

                // Execute wc -l to count matching directory entries
                execlp("wc", "wc", "-l", NULL);
            } else {
                // Parent process

                // Close all pipe descriptors in the parent
                close(fd1[0]);
                close(fd1[1]);
                close(fd2[0]);
                close(fd2[1]);

                // Wait for all three child processes to finish
                wait(NULL);
                wait(NULL);
                wait(NULL);
            }
        }
    }

    return 0;
}

/*
==========================================================================================================================
Output : After creating a new test directory using mkdir testdir, i received output as 1
==========================================================================================================================
*/

