
/*
==========================================================================================================================
Name : 38b.c
Author : Hetul Mehta
Description : FIFO Communication (Two-Way): Write two programs to establish communication
through FIFO using two-way communication.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char msg[100], buf[100];

    int fd1 = open("fifo1", O_RDWR);  // Open fifo1 for communication with Program 1
    int fd2 = open("fifo2", O_RDWR);  // Open fifo2 for communication with Program 1

    // Receive the message sent by Program 1 through fifo1
    read(fd1, buf, 100);

    printf("Message received from Program 1: %s", buf);

    printf("Enter message to send to Program 1: ");
    fgets(msg, 100, stdin);  // Read the reply from the user

    // Send the reply to Program 1 through fifo2
    write(fd2, msg, strlen(msg) + 1);

    close(fd1);  // Close fifo1
    close(fd2);  // Close fifo2

    return 0;
}

/*
==========================================================================================================================
Output :
Message received from Program 1: Hello
Enter message to send to Program 1: how are you

==========================================================================================================================
*/

