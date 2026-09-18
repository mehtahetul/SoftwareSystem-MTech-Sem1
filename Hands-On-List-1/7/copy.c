/*
==========================================================================================================================
Name : copy.c
Author : Hetul Mehta
Description : C program to copy contents of file1 into file2 using system calls.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main()
{
    int src_fd, dest_fd;
    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    src_fd = open("source.txt", O_RDONLY);

    if(src_fd == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    dest_fd = open("dest.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(dest_fd == -1)
    {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }

    while((bytes_read = read(src_fd, buffer, BUF_SIZE)) > 0)
    {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    printf("File copy completed successfully.\n");

    return 0;
}

/*
==========================================================================================================================
Output : 
Enter data for source file (Ctrl+D to stop):
Hello My name is hetul mehta.
I am checking if a file is copied successfully or not.

Executing ls command to check the creation of dest.txt
7  copy.c  dest.txt  source.txt

Printing the content of dest.txt to check if it has been copied properly or not.
Hello My name is hetul mehta.
I am checking if a file is copied successfully or not.

File copy completed successfully.
==========================================================================================================================
*/