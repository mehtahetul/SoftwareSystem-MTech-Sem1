
/*
==========================================================================================================================
Name : 38a.c
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

    int fd1 = open("fifo1", O_RDWR);  // Open fifo1 for communication with Program 2
    int fd2 = open("fifo2", O_RDWR);  // Open fifo2 for communication with Program 2

    printf("Enter message to send to Program 2: ");
    fgets(msg, 100, stdin);  // Read the message from the user

    // Send the message to Program 2 through fifo1
    write(fd1, msg, strlen(msg) + 1);

    // Receive the reply from Program 2 through fifo2
    read(fd2, buf, 100);

    printf("Message received from Program 2: %s", buf);

    close(fd1);  // Close fifo1
    close(fd2);  // Close fifo2

    return 0;
}

/*
==========================================================================================================================
Output :
Enter message to send to Program 2: Hello
Message received from Program 2: how are you

==========================================================================================================================
*/

