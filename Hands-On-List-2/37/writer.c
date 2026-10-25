
/*
==========================================================================================================================
Name : 37a.c
Author : Hetul Mehta
Description : FIFO Communication (One-Way): Write two programs to enable communication
through FIFO using one-way communication.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    mkfifo("myfifo", 0666);  // Create a FIFO named myfifo

    int fd = open("myfifo", O_WRONLY);  // Open FIFO in write-only mode

    char msg[200];

    // Read the message entered by the user
    fgets(msg, sizeof(msg), stdin);

    // Write the message into the FIFO, including the null terminator
    write(fd, msg, strlen(msg) + 1);

    close(fd);  // Close the FIFO

    return 0;
}

/*
==========================================================================================================================
Output :
Hello
==========================================================================================================================
*/

