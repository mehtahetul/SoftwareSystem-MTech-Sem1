
/*
============================================================================
Name        : 57.c
Author      : Hetul Mehta
Description : Program to print system limitations:
              a. Maximum length of arguments to exec family functions
              b. Maximum number of simultaneous processes per user ID
              c. Number of clock ticks per second
              d. Maximum number of open files
              e. Size of a page
              f. Total number of physical memory pages
              g. Number of currently available physical memory pages
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Max length of arguments to exec: %ld bytes\n",
           sysconf(_SC_ARG_MAX));

    printf("Max number of processes per user ID: %ld\n",
           sysconf(_SC_CHILD_MAX));

    printf("Number of clock ticks per second: %ld\n",
           sysconf(_SC_CLK_TCK));

    printf("Max number of open files: %ld\n",
           sysconf(_SC_OPEN_MAX));

    printf("Page size: %ld bytes\n",
           sysconf(_SC_PAGESIZE));

    printf("Total number of pages in physical memory: %ld\n",
           sysconf(_SC_PHYS_PAGES));

    printf("Available number of pages in physical memory: %ld\n",
           sysconf(_SC_AVPHYS_PAGES));

    return 0;
}

/*
============================================================================
Sample Output (values vary by system):
Max length of arguments to exec: 2097152 bytes
Max number of processes per user ID: 6838
Number of clock ticks per second: 100
Max number of open files: 1024
Page size: 4096 bytes
Total number of pages in physical memory: 672780
Available number of pages in physical memory: 19484
============================================================================
*/

