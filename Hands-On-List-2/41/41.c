
/*
==========================================================================================================================
Name : 41.c
Author : Hetul Mehta
Description : Message Queue Creation: Write a program to create a message queue, and print
the key and message queue ID.
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    // Generate a unique key using progfile and project identifier 65
    key_t key = ftok("progfile", 65);

    // Create a message queue or access an existing queue with the same key
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Print the generated key and message queue ID
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
==========================================================================================================================
Output :
Key: 1090583618
Message Queue ID: 1

==========================================================================================================================
*/

