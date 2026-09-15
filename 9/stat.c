/*
==========================================================================================================================
Name : stat.c
Author : Hetul Mehta
Description : C program to print information about a given file.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct stat fileStat;

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(stat(argv[1], &fileStat) < 0)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", argv[1]);
    printf("a. Inode: %ld\n", (long)fileStat.st_ino);
    printf("b. Number of hard links: %ld\n", (long)fileStat.st_nlink);
    printf("c. UID: %d\n", fileStat.st_uid);
    printf("d. GID: %d\n", fileStat.st_gid);
    printf("e. Size: %ld bytes\n", (long)fileStat.st_size);
    printf("f. Block size: %ld bytes\n", (long)fileStat.st_blksize);
    printf("g. Number of blocks: %ld\n", (long)fileStat.st_blocks);
    printf("h. Time of last access: %s", ctime(&fileStat.st_atime));
    printf("i. Time of last modification: %s", ctime(&fileStat.st_mtime));
    printf("j. Time of last status change: %s", ctime(&fileStat.st_ctime));

    return 0;
}

/*
==========================================================================================================================
Command executed: ./9 Hands-on\ List\ 1.pdf 
Output : 
File: text.txt
a. Inode: 784988
b. Number of hard links: 1
c. UID: 1000
d. GID: 1000
e. Size: 12 bytes
f. Block size: 4096 bytes
g. Number of blocks: 8
h. Time of last access: Tue Sep 15 09:30:05 2026
i. Time of last modification: Tue Sep 15 09:30:05 2026
j. Time of last status change: Tue Sep 15 09:30:05 2026
==========================================================================================================================
*/