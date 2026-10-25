
/*
==========================================================================================================================
Name : 33.c
Author : Hetul Mehta
Description : Two-Way Communication: Write a program to send and receive data between the
parent and child processes using two-way communication.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1[2], fd2[2];  // Two pipes: fd1 for parent-to-child and fd2 for child-to-parent
    pid_t pid;

    char parent_msg[100], child_msg[100], buffer[100];

    pipe(fd1);  // Create the pipe for communication from parent to child
    pipe(fd2);  // Create the pipe for communication from child to parent

    pid = fork();  // Create a child process

    if (pid > 0) {
        // Parent process

        printf("Parent: Enter message for child: ");
        fgets(parent_msg, sizeof(parent_msg), stdin);  // Read message entered by the parent

        // Send the message to the child through fd1
        write(fd1[1], parent_msg, strlen(parent_msg) + 1);

        // Receive the reply from the child through fd2
        read(fd2[0], buffer, sizeof(buffer));

        printf("Parent received: %s\n", buffer);
    } else {
        // Child process

        // Read the message sent by the parent
        read(fd1[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        printf("Child: Enter message for parent: ");
        fgets(child_msg, sizeof(child_msg), stdin);  // Read message entered by the child

        // Send the reply to the parent through fd2
        write(fd2[1], child_msg, strlen(child_msg) + 1);
    }

    return 0;
}

/*
==========================================================================================================================
Output :
Parent: Enter message for child: Hello child
Child received: Hello child

Child: Enter message for parent: Bye parent
Parent received: Bye parent

==========================================================================================================================
*/

