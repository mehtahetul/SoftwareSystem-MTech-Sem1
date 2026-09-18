/*
==========================================================================================================================
Name : 21_forkwrite.c
Author : Hetul Mehta
Description : C program to open a file, call fork, and allow both parent and child processes to write to the file.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        write(fd, "Child writing\n", 14);
    }
    else {
        write(fd, "Parent writing\n", 15);
    }

    close(fd);

    return 0;
}

/*
==========================================================================================================================
Output : 
Parent Process ID: 5663
child process: 5664, 5663
==========================================================================================================================
*/