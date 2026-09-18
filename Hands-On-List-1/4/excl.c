/*
==========================================================================================================================
Name : 4.c
Author : Hetul Mehta
Description : C program to open an existing file in read-write mode and experiment with O_EXCL flag.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    const char *filename = "test.txt";
    int fd;

    printf("Trying to open a file using O_RDWR\n");

    fd = open(filename, O_RDWR);

    if(fd == -1)
    {
        perror("open");
    }
    else
    {
        printf("File opened successfully. fd = %d\n", fd);
        close(fd);
    }

    printf("\nTrying to create a file using O_CREAT | O_EXCL\n");

    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);

    if(fd == -1)
    {
        perror("open");
    }
    else
    {
        printf("File created successfully. fd = %d\n", fd);
        close(fd);
    }

    printf("\nTrying O_CREAT | O_EXCL again on the same file\n");

    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);

    if(fd == -1)
    {
        perror("open");
    }
    else
    {
        printf("File opened. fd = %d\n", fd);
        close(fd);
    }

    return 0;
}

/*
==========================================================================================================================

Output :
Trying to open a file using O_RDWR
open: No such file or directory

Trying to create a file using O_CREAT | O_EXCL
File created successfully. fd = 3

Trying O_CREAT | O_EXCL again on the same file
open: File exists



The open() system call is used to open a file. The O_RDWR flag opens the file in read-write mode. If the file does not exist, O_RDWR alone cannot create it.

O_CREAT is used to create the file if it does not exist, while O_EXCL ensures that the call fails if the file already exists. Therefore, O_CREAT | O_EXCL creates the file on the first attempt and gives File exists on the second attempt.


First: O_RDWR fails because test.txt doesn't exist.
Second: O_CREAT | O_EXCL creates test.txt.
Third: The file already exists, so O_EXCL causes open() to fail with File exists.

==========================================================================================================================
*/