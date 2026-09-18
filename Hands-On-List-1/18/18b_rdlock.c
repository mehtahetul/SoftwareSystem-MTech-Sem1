/*
==========================================================================================================================
Name : 18b_rdlock.c
Author : Hetul Mehta
Description : C program to implement record-level read locking.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define RECORD_SIZE 50
#define NUM_RECORDS 3

void lock_record(int fd, int record_num) {
    struct flock lock;

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_num * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    printf("Trying to acquire read lock on record %d...\n", record_num);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("Read lock acquired on record %d by PID %d\n",
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

    printf("Read lock released on record %d\n", record_num);
}

int main() {
    int fd = open("records.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    int record_num;

    printf("Enter record number to lock and read (0-2): ");
    scanf("%d", &record_num);

    if (record_num < 0 || record_num >= NUM_RECORDS) {
        printf("Invalid record number!\n");
        close(fd);
        return 1;
    }

    lock_record(fd, record_num);

    char buffer[RECORD_SIZE + 1];

    pread(fd, buffer, RECORD_SIZE,
          record_num * RECORD_SIZE);

    buffer[RECORD_SIZE] = '\0';

    printf("Record %d data: %s\n", record_num, buffer);

    printf("Press Enter to release the lock...");
    getchar();
    getchar();

    unlock_record(fd, record_num);

    close(fd);

    return 0;
}

/*
==========================================================================================================================
hetul@hetul:~/Desktop/hands-on-1/18$ ./18b
Enter record number to lock and read (0-2): 1
Trying to acquire read lock on record 1...
Read lock acquired on record 1 by PID 4784
Record 1 data: Hello, my name is Hetul.
Press Enter to release the lock...
Read lock released on record 1
==========================================================================================================================
*/