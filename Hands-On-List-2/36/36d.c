
/*
==========================================================================================================================
Name : 36d.c
Author : Hetul Mehta
Description : FIFO File Creation: Create a FIFO file using the mknod system call.
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Create a FIFO named myfifo with read and write permissions
    if (mknod("myfifo3", S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        return 1;
    }

    printf("FIFO created successfully using mknod system call.\n");

    return 0;
}

/*
==========================================================================================================================
Output :
FIFO created successfully using mknod system call.
==========================================================================================================================
*/

