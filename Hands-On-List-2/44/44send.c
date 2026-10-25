
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;
    message.mtype = 1;

    printf("Enter message: ");
    fgets(message.mtext, sizeof(message.mtext), stdin);
    message.mtext[strcspn(message.mtext, "\n")] = '\0';

    msgsnd(msgid, &message, sizeof(message.mtext), 0);
    printf("Message sent\n");

    return 0;
}

