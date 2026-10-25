
/*
============================================================================
Name        : 52.c
Author      : Hetul Mehta
Description : Write a program to create a concurrent server:
              a. Use fork
              b. Use pthread_create
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 8080

void handle_client(int client_sock)
{
    char buffer[1024];
    int n;

    while ((n = read(client_sock, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[n] = '\0';

        printf("Client message: %s\n", buffer);

        send(client_sock, buffer, n, 0);
    }

    close(client_sock);
    printf("Client disconnected.\n");
}

void *thread_func(void *arg)
{
    int client_sock = *(int *)arg;
    free(arg);

    handle_client(client_sock);

    return NULL;
}

int main()
{
    int server_fd, client_sock, mode;
    struct sockaddr_in addr;
    socklen_t addrlen;

    printf("Choose mode:\n");
    printf("1. fork\n");
    printf("2. pthread_create\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    if (mode != 1 && mode != 2)
    {
        printf("Invalid choice\n");
        return 1;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    /*
       Prevent zombie child processes in fork mode.
    */
    signal(SIGCHLD, SIG_IGN);

    printf("Server running on port number %d\n", PORT);

    while (1)
    {
        addrlen = sizeof(addr);

        client_sock = accept(server_fd,
                             (struct sockaddr *)&addr, &addrlen);

        if (client_sock < 0)
        {
            perror("accept");
            continue;
        }

        if (mode == 1)
        {
            pid_t pid = fork();

            if (pid == 0)
            {
                /* Child process handles the client. */
                close(server_fd);
                handle_client(client_sock);
                exit(0);
            }
            else if (pid > 0)
            {
                /* Parent continues accepting clients. */
                close(client_sock);
            }
            else
            {
                perror("fork");
                close(client_sock);
            }
        }
        else
        {
            /* Create a separate thread for each client. */
            pthread_t tid;
            int *client_ptr = malloc(sizeof(int));

            if (client_ptr == NULL)
            {
                perror("malloc");
                close(client_sock);
                continue;
            }

            *client_ptr = client_sock;

            if (pthread_create(&tid, NULL, thread_func, client_ptr) != 0)
            {
                perror("pthread_create");
                free(client_ptr);
                close(client_sock);
                continue;
            }

            pthread_detach(tid);
        }
    }

    close(server_fd);
    return 0;
}

/*
============================================================================
Sample Output (fork mode):
Choose mode:
1. fork
2. pthread_create
Enter choice: 1
Server running on port number 8080
Client message: This message is from client
Client disconnected.
============================================================================
*/

