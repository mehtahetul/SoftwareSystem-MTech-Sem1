/*
==========================================================================================================================
Name : 17a_ticket_init.c
Author : Hetul Mehta
Description : C program to initialize the ticket.txt file with a ticket number.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("ticket.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    int ticket = 100;
    char buffer[10];

    sprintf(buffer, "%d\n", ticket);
    int len = strlen(buffer);

    if (write(fd, buffer, len) == -1) {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }

    close(fd);

    printf("Ticket file initialized with number: %d\n", ticket);

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/17$ gcc 17a_ticket_init.c -o 17a
gcc 17b_ticket.c -o 17b
hetul@hetul:~/Desktop/hands-on-1/17$ ./17a
Ticket file initialized with number: 100
hetul@hetul:~/Desktop/hands-on-1/17$ ./17b
New ticket reserved: 101
hetul@hetul:~/Desktop/hands-on-1/17$ ./17b
New ticket reserved: 102
hetul@hetul:~/Desktop/hands-on-1/17$ ./17b
New ticket reserved: 103
==========================================================================================================================
*/