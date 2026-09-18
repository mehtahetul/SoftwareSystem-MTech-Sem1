/*
==========================================================================================================================
Name : 28_nice.c
Author : Hetul Mehta
Description : C program to display the current process priority and modify it using nice.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {

    int priority = nice(0);

    printf("Current nice value: %d\n", priority);

    priority = nice(5);

    if (priority == -1 && errno != 0) {
        perror("nice");
        return 1;
    }

    printf("New nice value: %d\n", priority);

    return 0;
}

/*
==========================================================================================================================
Current nice value: 0
New nice value: 5
==========================================================================================================================
*/