
/*
==========================================================================================================================
Name : 46.c
Author : Hetul Mehta
Description : Removing Message Queue: Write a program to remove the message queue.
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    // Generate the key using progfile and project identifier 65
    key_t key = ftok("progfile", 65);

    // Access the existing message queue
    int msgid = msgget(key, 0666);

    // Remove the message queue from the system
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

/*
==========================================================================================================================
Output :

==========================================================================================================================
*/

