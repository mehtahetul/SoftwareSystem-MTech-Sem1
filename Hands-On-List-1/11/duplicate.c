/*
==========================================================================================================================
Name : duplicate.c
Author : Hetul Mehta
Description : C program to duplicate a file descriptor and append the file using dup(), dup2() and fcntl().
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }

    // a. Using dup()
    int fd1 = dup(fd);
    dprintf(fd1, "Written using dup() fd\n");

    // b. Using dup2()
    int fd2 = 10;
    dup2(fd, fd2);
    dprintf(fd2, "Written using dup2() fd\n");

    // c. Using fcntl()
    int fd3 = fcntl(fd, F_DUPFD, 0);
    dprintf(fd3, "Written using fcntl() fd\n");

    // Original descriptor
    dprintf(fd, "Written using original fd.\n");

    close(fd);
    close(fd1);
    close(fd2);
    close(fd3);

    // Verify file contents
    char temp[100];

    int fd4 = open("temp.txt", O_RDONLY);

    ssize_t ch = read(fd4, temp, 99);
    temp[ch] = '\0';

    printf("The following is written in the file-\n\n%s", temp);

    close(fd4);

    return 0;
}
/*
==========================================================================================================================
Output : 
The following is written in the file-

Written using dup() fd
Written using dup2() fd
Written using fcntl() fd
Written using original fd.
==========================================================================================================================
*/