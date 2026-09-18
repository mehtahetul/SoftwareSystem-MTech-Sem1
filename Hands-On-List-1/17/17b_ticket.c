/*
==========================================================================================================================
Name : 17b_ticket.c
Author : Hetul Mehta
Description : C program to reserve a ticket using a write lock.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("ticket.txt", O_RDWR);

    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    // Wait until the write lock is available
    fcntl(fd, F_SETLKW, &lock);

    char buffer[20];

    int n = read(fd, buffer, sizeof(buffer) - 1);

    if (n <= 0) {
        perror("Error reading file");
        close(fd);
        exit(1);
    }

    buffer[n] = '\0';

    int ticket = atoi(buffer);
    ticket++;

    lseek(fd, 0, SEEK_SET);

    int len = sprintf(buffer, "%d\n", ticket);
    write(fd, buffer, len);

    printf("New ticket reserved: %d\n", ticket);

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}
