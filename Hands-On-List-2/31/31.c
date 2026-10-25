
/*
==========================================================================================================================
Name : 14.c
Author : Hetul Mehta
Description : Simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // File descriptors for the pipe: fd[0] for reading, fd[1] for writing

    char write_msg[] = "Pipe Communication";  // Message to be written into the pipe
    char read_msg[100];  // Buffer to store the message read from the pipe

    pipe(fd);  // Create a pipe and initialize its read and write file descriptors

    // Write the message into the write end of the pipe, including the null character
    write(fd[1], write_msg, strlen(write_msg) + 1);

    // Read the message from the read end of the pipe
    read(fd[0], read_msg, sizeof(read_msg));

    // Display the message received from the pipe
    printf("Message read: %s\n", read_msg);

    return 0;
}

/*
==========================================================================================================================
Output :
Message read: Pipe Communication
==========================================================================================================================
*/

