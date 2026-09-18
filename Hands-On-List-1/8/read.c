/*
==========================================================================================================================
Name : read.c
Author : Hetul Mehta
Description : C program to read a file line by line and display each line as it is read.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("text.txt", O_RDONLY);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }

    char ch;
    char line[1024];
    int idx = 0;

    while(read(fd, &ch, 1) > 0)
    {
        if(ch == '\n')
        {
            line[idx] = '\0';
            printf("%s\n", line);
            idx = 0;
        }
        else
        {
            line[idx++] = ch;

            if(idx >= sizeof(line) - 1)
            {
                line[idx] = '\0';
                printf("%s\n", line);
                idx = 0;
            }
        }
    }

    close(fd);

    return 0;
}


/*
==========================================================================================================================
Output : 
My name is Hetul Mehta.
I am doing the 8th practical of Software Systems.
Reading file line by line.

==========================================================================================================================
*/