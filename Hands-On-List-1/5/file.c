/*
==========================================================================================================================
Name : file.c
Author : Hetul Mehta
Description : C program to create five new files with infinite loop and eecute the program in the background
              and check the file descriptor table at /proc/pid/fd
Date: 15th Sept, 2025.
==========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd[5];

    for(int i = 0; i < 5; i++)
    {
        char filename[20];

        sprintf(filename, "file%d.txt", i + 1);

        fd[i] = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

        printf("Created %s (fd = %d)\n", filename, fd[i]);
    }

    printf("Process running... PID = %d\n", getpid());

    while(1)
    {
        sleep(1);
    }

    return 0;
}
/*
==========================================================================================================================
Output : Created file1.txt (fd = 3)
         Created file2.txt (fd = 4)
         Created file3.txt (fd = 5)
         Created file4.txt (fd = 6)
         Created file5.txt (fd = 7)

         Compiling file1.c...
         Executing file1.c...

         3740

         Now in another terminal we write the command : cd /proc/p7710 and then when
         we execute cat status, it will show the status of the file1.c  being executed
         in the background.

         Now in the main terminal we kill the process. : kill 3740
         Here, kill command kills (terminates) the process and does not delete.
==========================================================================================================================
*/