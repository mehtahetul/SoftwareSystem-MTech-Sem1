/*
==========================================================================================================================
Name : inout.c
Author : Hetul Mehta
Description : C program to take input from STDIN and display it on STDOUT using read/write system calls.
Date: 15th Sept, 2026.
==========================================================================================================================
*/

#include <unistd.h>
#include <stdio.h>

int main()
{
    char buffer[1024];
    ssize_t bytesRead;

    printf("Taking string from STDIN\n");

    bytesRead = read(0, buffer, sizeof(buffer));

    write(1, buffer, bytesRead);

    return 0;
}

/*
==========================================================================================================================
Output : 

Taking string from STDIN 
Hello My name is Hetul Mehta.
Hello My name is Hetul Mehta.

==========================================================================================================================
*/
