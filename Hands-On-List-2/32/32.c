
/*
==========================================================================================================================
Name : 32.c
Author : Hetul Mehta
Description : Simple program to send some data from parent to the child process.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    pid_t pid;  // Stores the process ID returned by fork()

    char msg[] = "Data for child";  // Message to be sent by the parent
    char buffer[100];  // Buffer to store the message received by the child

    pipe(fd);  // Create a pipe for communication
    pid = fork();  // Create a child process

    if (pid == 0) {
        // Child process

        close(fd[1]);  // Close the write end of the pipe

        // Read the message sent by the parent
        read(fd[0], buffer, sizeof(buffer));

        // Display the received message
        printf("Child received: %s\n", buffer);

        close(fd[0]);  // Close the read end of the pipe
    } else {
        // Parent process

        close(fd[0]);  // Close the read end of the pipe

        // Write the message into the pipe, including the null terminator
        write(fd[1], msg, strlen(msg) + 1);

        close(fd[1]);  // Close the write end of the pipe
    }

    return 0;
}

/*
==========================================================================================================================
Output :
Child received: Data for child
==========================================================================================================================
*/

