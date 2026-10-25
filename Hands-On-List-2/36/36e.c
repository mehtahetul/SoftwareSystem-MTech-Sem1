/*
==========================================================================================================================
Name : 36e.c
Author : Hetul Mehta
Description : FIFO File Creation: Create a FIFO file using the mkfifo library function.
==========================================================================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    // Create a FIFO named myfifo with read and write permissions
    if (mkfifo("myfifo4", 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully using mkfifo library function.\n");

    return 0;
}

/*
==========================================================================================================================
Output :
FIFO created successfully using mkfifo library function.
==========================================================================================================================
*/
