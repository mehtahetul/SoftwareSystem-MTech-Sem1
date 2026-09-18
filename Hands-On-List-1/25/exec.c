/*
==========================================================================================================================
Name : 25_exec.c
Author : Hetul Mehta
Description : C program to execute another executable using the exec system call and pass an argument to it.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc > 1) {
        char *args[] = {"./a", argv[1], NULL};
        execvp(args[0], args);
    }
    else {
        char *args[] = {"./a", "name", NULL};
        execvp(args[0], args);
    }

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/25$ ./exec
Hello, name
hetul@hetul:~/Desktop/hands-on-1/25$ ./exec Hetul
Hello, Hetul
hetul@hetul:~/Desktop/hands-on-1/25$ ./exec Virat Kohli
Hello, Virat
==========================================================================================================================
*/