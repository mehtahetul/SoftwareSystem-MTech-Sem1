
/*
==========================================================================================================================
Name : 43.c
Author : Hetul Mehta
Description : Sending Messages to Message Queue: Write a program to send messages to the
message queue. Check using $ipcs -q.
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
    long mtype;       // Message type (must be greater than 0)
    char mtext[100];  // Message content
};

int main() {
    // Generate a key using progfile and project identifier 65
    key_t key = ftok("progfile", 65);

    // Create a message queue or access an existing queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;

    message.mtype = 1;  // Set the message type to 1

    printf("Enter message: ");

    // Read the message from the user
    fgets(message.mtext, sizeof(message.mtext), stdin);

    // Remove the trailing newline character, if present
    message.mtext[strcspn(message.mtext, "\n")] = '\0';

    // Send the message to the queue
    msgsnd(msgid, &message, sizeof(message.mtext), 0);

    printf("Message sent\n");

    return 0;
}

/*
==========================================================================================================================
Output :
Enter message: Hello, How are you?
Message sent

On inspecting with ipcs -q
key        msqid      owner      perms      used-bytes   messages
0x4100fc40 1          hetul      666        100          1    
==========================================================================================================================
*/

