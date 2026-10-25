
/*
============================================================================
Name        : 55.c
Author      : Hetul Mehta
Description : Write a program to set a system resource limit using the
              setrlimit system call.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

void print_limit(int resource, const char *name)
{
    struct rlimit rl;

    if (getrlimit(resource, &rl) == 0)
    {
        if (rl.rlim_cur == RLIM_INFINITY)
            printf("%s soft limit: unlimited, ", name);
        else
            printf("%s soft limit: %ld, ",
                   name, (long)rl.rlim_cur);

        if (rl.rlim_max == RLIM_INFINITY)
            printf("hard limit: unlimited\n");
        else
            printf("hard limit: %ld\n", (long)rl.rlim_max);
    }
    else
    {
        perror("getrlimit");
    }
}

int main()
{
    struct rlimit limit;

    printf("Before:\n");
    print_limit(RLIMIT_FSIZE, "File size");

    limit.rlim_cur = 1024 * 1024;       // Soft limit: 1 MB
    limit.rlim_max = 2 * 1024 * 1024;   // Hard limit: 2 MB

    if (setrlimit(RLIMIT_FSIZE, &limit) == -1)
    {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    printf("\nAfter:\n");
    print_limit(RLIMIT_FSIZE, "File size");

    return 0;
}

/*
============================================================================
Sample Output:
Before:
File size soft limit: unlimited, hard limit: unlimited

After:
File size soft limit: 1048576, hard limit: 2097152
============================================================================
*/

