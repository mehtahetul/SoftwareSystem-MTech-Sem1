/*
==========================================================================================================================
Name : 18a_wrlock.c
Author : Hetul Mehta
Description : C program to implement record-level write locking.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define RECORD_SIZE 50
#define NUM_RECORDS 3

void lock_record(int fd, int record_num) {
    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    printf("Trying to acquire write lock on record %d...\n", record_num);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("Write lock acquired on record %d by PID %d\n",
           record_num, getpid());
}

void unlock_record(int fd, int record_num) {
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    fcntl(fd, F_SETLK, &lock);

    printf("Write lock released on record %d\n", record_num);
}

int main() {
    int fd = open("records.txt", O_RDWR | O_CREAT, 0666);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Create 3 records if file is empty
    off_t size = lseek(fd, 0, SEEK_END);

    if (size == 0) {
        char buffer[RECORD_SIZE];

        for (int i = 0; i < NUM_RECORDS; i++) {
            snprintf(buffer, RECORD_SIZE,
                     "Record %d: Initial data", i);

            write(fd, buffer, RECORD_SIZE);
        }
    }

    int record_num;

    printf("Enter record number to lock and modify (0-2): ");
    scanf("%d", &record_num);

    if (record_num < 0 || record_num >= NUM_RECORDS) {
        printf("Invalid record number!\n");
        close(fd);
        return 1;
    }

    lock_record(fd, record_num);

    char buffer[RECORD_SIZE];

    printf("Enter new data: ");
    getchar();
    fgets(buffer, RECORD_SIZE, stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    pwrite(fd, buffer, RECORD_SIZE,
           record_num * RECORD_SIZE);

    printf("Record %d modified successfully.\n", record_num);

    printf("Press Enter to release the lock...");
    getchar();

    unlock_record(fd, record_num);

    close(fd);

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/18$ ./18a
Enter record number to lock and modify (0-2): 1 
Trying to acquire write lock on record 1...
Write lock acquired on record 1 by PID 4733
Enter new data: Hello, my name is Hetul.
Record 1 modified successfully.
Press Enter to release the lock...
Write lock released on record 1

==========================================================================================================================
*/