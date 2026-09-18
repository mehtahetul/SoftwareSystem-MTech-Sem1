#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    const char *filename = "test10b.txt";
    char data[] = "UBUNTU CS\n";

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

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
    printf("Position after first write: %ld\n", (long)pos);

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
Here we are creating a new file.
0000000   U   B   U   N   T   U       C   S  \n  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   U   B   U   N   T   U       C   S  \n
0000036
==========================================================================================================================
*/