
/*
==========================================================================================================================
Name : 42.c
Author : Hetul Mehta
Description : Message Queue Information: Write a program to print information about a
message queue using msqid_ds and ipc_perm structures:
a. Access permission
b. UID, GID
c. Time of last message sent and received
d. Time of last change in the message queue
e. Size of the queue
f. Number of messages in the queue
g. Maximum number of bytes allowed
h. PID of the msgsnd and msgrcv
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    // Generate a key using progfile and project identifier 65
    key_t key = ftok("progfile", 65);

    // Create a message queue or access an existing queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Structure to store message queue information
    struct msqid_ds buf;

    // Retrieve the current message queue information
    msgctl(msgid, IPC_STAT, &buf);

    // Display access permissions
    printf("Access permissions: %o\n", buf.msg_perm.mode);

    // Display owner user ID and group ID
    printf("UID: %d\n", buf.msg_perm.uid);
    printf("GID: %d\n", buf.msg_perm.gid);

    // Display the time of the last message sent and received
    printf("Last message sent: %s", ctime(&buf.msg_stime));
    printf("Last message received: %s", ctime(&buf.msg_rtime));

    // Display the time when the queue was last changed
    printf("Last change: %s", ctime(&buf.msg_ctime));

    // Display the current number of bytes stored in the queue
    printf("Queue size: %ld\n", (long)buf.__msg_cbytes);

    // Display the number of messages currently in the queue
    printf("Number of messages: %ld\n", (long)buf.msg_qnum);

    // Display the maximum number of bytes allowed in the queue
    printf("Max bytes allowed: %ld\n", (long)buf.msg_qbytes);

    // Display the PIDs of the last sender and receiver
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}

/*
==========================================================================================================================
Output :
Access permissions: 666
UID: 1000
GID: 1000
Last message sent: Thu Jan  1 05:30:00 1970
Last message received: Thu Jan  1 05:30:00 1970
Last change: Thu Oct 22 22:22:49 2026
Queue size: 0
Number of messages: 0
Max bytes allowed: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0

==========================================================================================================================
*/

