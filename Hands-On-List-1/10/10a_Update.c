#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    const char *filename = "text.txt";
    char data[] = "UBUNTU CS\n";

    int fd = open(filename, O_RDWR | O_CREAT, 0644);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }

    ssize_t written = write(fd, data, 10);

    if(written != 10)
    {
        perror("write");
        close(fd);
        return 1;
    }

    off_t pos = lseek(fd, 0, SEEK_CUR);
    printf("Current position: %ld\n", (long)pos);

    pos = lseek(fd, 10, SEEK_CUR);

    if(pos == (off_t)-1)
    {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Position after lseek: %ld\n", (long)pos);

    written = write(fd, data, 10);

    if(written != 10)
    {
        perror("write");
        close(fd);
        return 1;
    }

    pos = lseek(fd, 0, SEEK_CUR);
    printf("Final position: %ld\n", (long)pos);

    close(fd);

    return 0;
}

/*
==========================================================================================================================
Output : 
Here we are using the existing file. Here what will happen is that the data will be overwritten.
My name is Hetul.
I am doing 10th practical of SS.
0000000   M   y       n   a   m   e       i   s       H   e   t   u   l
0000020   .  \n   I       a   m       d   o   i   n   g       1   0   t
0000040   h       p   r   a   c   t   i   c   a   l       o   f       S
0000060   S   .  \n
0000063
==========================================================================================================================
*/