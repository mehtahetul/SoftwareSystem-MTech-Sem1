/*
==========================================================================================================================
Name : 3.c
Author : Hetul Mehta
Description : C program to create a file and print the file descriptor value using creat() system call.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    const char *filename = "3_create.txt";

    fd = creat(filename, 0644);

    printf("File Created.\n");
    printf("fd = %d\n", fd);

    return 0;
}

/*
==========================================================================================================================
Output : hetul@hetul:~/Desktop/hands-on-1/3$ ./3
         File Created.
         fd = 3
==========================================================================================================================
*/
