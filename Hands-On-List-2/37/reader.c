
/*
==========================================================================================================================
Name : 37b.c
Author : Hetul Mehta
Description : FIFO Communication (One-Way): Write two programs to enable communication
through FIFO using one-way communication.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    mkfifo("myfifo", 0666);  // Create a FIFO if it does not already exist

    int fd = open("myfifo", O_RDONLY);  // Open FIFO in read-only mode

    char msg[200];

    // Read the message sent by the writer
    ssize_t n = read(fd, msg, sizeof(msg) - 1);

    if (n > 0) {
        msg[n] = '\0';  // Add null terminator to make the data a valid string
        printf("%s", msg);  // Display the received message
    }

    close(fd);  // Close the FIFO

    return 0;
}

/*
==========================================================================================================================
Output :
Hello
==========================================================================================================================
*/

