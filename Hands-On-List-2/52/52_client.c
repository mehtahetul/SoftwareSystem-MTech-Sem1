
/*
============================================================================
Name        : 52_client.c
Author      : Hetul Mehta
Description : Client program for concurrent server communication.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0)
    {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char *msg = "This message is from client";

    send(sock, msg, strlen(msg), 0);

    int n = read(sock, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = '\0';
        printf("Message received from server: %s\n", buffer);
    }

    close(sock);
    return 0;
}

/*
============================================================================
Sample Output:
Message received from server: This message is from client
============================================================================
*/

