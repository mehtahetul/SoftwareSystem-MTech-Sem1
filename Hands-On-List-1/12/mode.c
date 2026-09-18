/*
==========================================================================================================================
Name : mode.c
Author : Hetul Mehta
Description : C program to find the opening mode of the file using fcntl().
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("test.txt", O_RDWR | O_APPEND);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);

    if((flags & O_ACCMODE) == O_RDONLY)
        printf("Opened: Read Only\n");
    else if((flags & O_ACCMODE) == O_WRONLY)
        printf("Opened: Write Only\n");
    else if((flags & O_ACCMODE) == O_RDWR)
        printf("Opened: Read/Write\n");

    if(flags & O_APPEND)
        printf("Opened with Append\n");

    if(flags & O_NONBLOCK)
        printf("Opened in Non-blocking mode\n");

    close(fd);

    return 0;
}

/*
==========================================================================================================================
Output : 
Opened: Read/Write
Opened with Append
==========================================================================================================================
*/