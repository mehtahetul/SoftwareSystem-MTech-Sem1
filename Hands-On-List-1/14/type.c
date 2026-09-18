/*
==========================================================================================================================
Name : type.c
Author : Hetul Mehta
Description : C program to identify the type of a file.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat fileStat;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(stat(argv[1], &fileStat) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    mode_t typeBits = fileStat.st_mode & S_IFMT;

    if(S_ISREG(fileStat.st_mode))
        printf("%s is a REGULAR FILE.\n", argv[1]);

    else if(S_ISDIR(fileStat.st_mode))
        printf("%s is a DIRECTORY.\n", argv[1]);

    else if(S_ISLNK(fileStat.st_mode))
        printf("%s is a SYMBOLIC LINK.\n", argv[1]);

    else if(S_ISCHR(fileStat.st_mode))
        printf("%s is a CHARACTER DEVICE FILE.\n", argv[1]);

    else if(S_ISBLK(fileStat.st_mode))
        printf("%s is a BLOCK DEVICE FILE.\n", argv[1]);

    else if(S_ISFIFO(fileStat.st_mode))
        printf("%s is a FIFO (named pipe).\n", argv[1]);

    else if(S_ISSOCK(fileStat.st_mode))
        printf("%s is a SOCKET.\n", argv[1]);

    else
        printf("%s is an UNKNOWN FILE TYPE.\n", argv[1]);

    return 0;
}

/*
==========================================================================================================================

hetul@hetul:~/Desktop/hands-on-1/14$ ./type
Usage: ./type <filename>

./type test.txt
test.txt is a REGULAR FILE.

./type testDirectory
testDirectory is a DIRECTORY.

ln -s test.txt link.txt
./type link.txt
link.txt is a REGULAR FILE.
Because stat() interprets a softlink file as regular file, if we want the output as 
softlink file then we need use lstat()
==========================================================================================================================
*/