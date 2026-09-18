/*
==========================================================================================================================
Name : 29_sched.c
Author : Hetul Mehta
Description : C program to get and modify the scheduling policy of a process.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

int main() {

    pid_t pid = getpid();
    int policy;
    struct sched_param param;

    // Get current scheduling policy
    policy = sched_getscheduler(pid);

    if (policy == SCHED_OTHER)
        printf("Current policy: SCHED_OTHER\n");
    else if (policy == SCHED_FIFO)
        printf("Current policy: SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("Current policy: SCHED_RR\n");

    // Set SCHED_FIFO with maximum real-time priority
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    // Check new policy
    policy = sched_getscheduler(pid);

    if (policy == SCHED_OTHER)
        printf("New policy: SCHED_OTHER\n");
    else if (policy == SCHED_FIFO)
        printf("New policy: SCHED_FIFO\n");
    else if (policy == SCHED_RR)
        printf("New policy: SCHED_RR\n");

    return 0;
}

/*
==========================================================================================================================
Current policy: SCHED_OTHER
New policy: SCHED_FIFO
==========================================================================================================================
*/
