
/*
============================================================================
Name        : 54.c
Author      : Hetul Mehta
Description : Write a program to print system resource limits using the
              getrlimit system call.
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
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data segment size");
    print_limit(RLIMIT_STACK, "Stack size");
    print_limit(RLIMIT_CORE, "Core file size");
    print_limit(RLIMIT_NOFILE, "Open files");

#ifdef RLIMIT_AS
    print_limit(RLIMIT_AS, "Virtual memory");
#endif

    return 0;
}

/*
============================================================================
Sample Output:
CPU time soft limit: unlimited, hard limit: unlimited
File size soft limit: unlimited, hard limit: unlimited
Data segment size soft limit: unlimited, hard limit: unlimited
Stack size soft limit: 8388608, hard limit: unlimited
Core file size soft limit: 0, hard limit: unlimited
Open files soft limit: 1024, hard limit: 524288
Virtual memory soft limit: unlimited, hard limit: unlimited
============================================================================
*/

