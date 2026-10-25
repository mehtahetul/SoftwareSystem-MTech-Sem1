
/*
==========================================================================================================================
Name : 39.c
Author : Hetul Mehta
Description : Waiting for Data in FIFO: Write a program to wait for data to be written into a FIFO
within 10 seconds, utilizing the select system call with the FIFO.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>

int main() {
    char *fifo = "/tmp/myfifo";  // Path of the FIFO

    mkfifo(fifo, 0666);  // Create the FIFO with read and write permissions

    int fd = open(fifo, O_RDONLY);  // Open FIFO in blocking read-only mode

    if (fd < 0) {
        perror("open");
        return 1;
    }

    fd_set rfds;  // File descriptor set for monitoring readability
    struct timeval tv;  // Structure to specify the timeout

    FD_ZERO(&rfds);  // Clear the file descriptor set
    FD_SET(fd, &rfds);  // Add the FIFO descriptor to the set

    tv.tv_sec = 10;  // Wait for a maximum of 10 seconds
    tv.tv_usec = 0;  // No additional microseconds

    // Wait until data is available or the timeout expires
    int ret = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (ret > 0 && FD_ISSET(fd, &rfds)) {
        // FIFO is ready for reading

        char buf[100];

        // Read the available data from the FIFO
        int n = read(fd, buf, sizeof(buf) - 1);

        if (n > 0) {
            buf[n] = '\0';  // Null-terminate the received data
            printf("Received: %s\n", buf);
        }
    } else if (ret == 0) {
        // No data arrived before the timeout
        printf("No data within 10 seconds.\n");
    } else if (ret < 0) {
        // select() encountered an error
        perror("select");
    }

    close(fd);  // Close the FIFO descriptor
    unlink(fifo);  // Remove the FIFO file

    return 0;
}

/*
==========================================================================================================================
Output :
Received: How are You

==========================================================================================================================
*/

