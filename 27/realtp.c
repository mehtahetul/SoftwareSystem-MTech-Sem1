/*
==========================================================================================================================
Name : 27_realtp.c
Author : Hetul Mehta
Description : C program to get the minimum and maximum real-time priority.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <sched.h>

int main() {

    int min = sched_get_priority_min(SCHED_FIFO);
    int max = sched_get_priority_max(SCHED_FIFO);

    printf("Min priority: %d\n", min);
    printf("Max priority: %d\n", max);

    return 0;
}


/*
==========================================================================================================================
Min priority: 1
Max priority: 99
==========================================================================================================================
*/