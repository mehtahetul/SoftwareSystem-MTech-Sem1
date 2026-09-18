/*
==========================================================================================================================
Name : 19_process_states.c
Author : Hetul Mehta
Description : C program to demonstrate running, sleeping and stopped process states.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {

    printf("PID: %d\n", getpid());

    while (1) {
        printf("Process is running...\n");
        sleep(1);
    }

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/19$ cat /proc/5343/status | grep State
State:	S (sleeping)
hetul@hetul:~/Desktop/hands-on-1/19$ cat /proc/5343/status | grep State
State:	T (stopped)

For R, when we remove "sleep(1)", it goes in infinite loop, thus showing it is in running state.
==========================================================================================================================
*/