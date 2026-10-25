
/*
==========================================================================================================================
Name : 44b.c
Author : Hetul Mehta
Description : Receiving Messages from Message Queue: Write a program to receive messages
from the message queue with IPC_NOWAIT as a flag.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msgbuf {
    long mtype;       // Message type
    char mtext[100];  // Message text
};

int main() {
    // Generate the key using the same file and project ID as the sender
    key_t key = ftok("progfile", 65);

    // Access the existing message queue or create it if it does not exist
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;

    // Try to receive a message of type 1 without waiting
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, IPC_NOWAIT) != -1) {
        printf("Received with IPC_NOWAIT flag: %s\n", message.mtext);
    } else if (errno == ENOMSG) {
        // No matching message is currently available
        printf("No message available with IPC_NOWAIT flag\n");
    } else {
        perror("msgrcv");
        return 1;
    }

    return 0;
}

/*
==========================================================================================================================
Output :

$ gcc 44send.c -o 44send
$ gcc 44a.c -o 44a
$ gcc 44b.c -o 44b

$ ./44send
Enter message: Hello
Message sent

$ ./44a
Received with 0 flag: Hello

$ ./44b
No message available with IPC_NOWAIT flag

==========================================================================================================================
*/

