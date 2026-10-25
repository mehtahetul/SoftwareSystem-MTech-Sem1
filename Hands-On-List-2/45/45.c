
/*
==========================================================================================================================
Name : 45.c
Author : Hetul Mehta
Description : Changing Message Queue Permissions: Write a program to change the existing
message queue permissions using the msqid_ds structure.
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

    // Structure to store message queue information
    struct msqid_ds buf;

    // Retrieve the current message queue information
    msgctl(msgid, IPC_STAT, &buf);

    // Display the existing permissions
    printf("Old permissions: %o\n", buf.msg_perm.mode);

    // Change the permissions to read-write for owner and read-only for group
    buf.msg_perm.mode = 0644;

    // Apply the updated permissions to the message queue
    msgctl(msgid, IPC_SET, &buf);

    // Retrieve the updated message queue information
    msgctl(msgid, IPC_STAT, &buf);

    // Display the new permissions
    printf("New permissions: %o\n", buf.msg_perm.mode);

    return 0;
}

/*
==========================================================================================================================
Output :
Old permissions: 666
New permissions: 644
==========================================================================================================================
*/

