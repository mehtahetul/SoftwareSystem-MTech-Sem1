/*
==========================================================================================================================
Name : 16a_wrlock.c
Author : Hetul Mehta
Description : C program to implement mandatory write lock.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    struct flock fl;

    fd = open("locked_file.txt", O_RDWR | O_CREAT, 0660);

    const char *msg = "Hands on list 1.\n";
    write(fd, msg, strlen(msg));

    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();

    fcntl(fd, F_SETLK, &fl);

    printf("Press Enter to release lock and exit.\n");
    getchar();

    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fl);

    close(fd);
    return 0;
}
/*
==========================================================================================================================
Press Enter to release lock and exit.

==========================================================================================================================
*/