/*
==========================================================================================================================
Name : input.c
Author : Hetul Mehta
Description : C program that accepts a command-line argument and prints it.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc > 1)
        printf("Hello, %s\n", argv[1]);
    else
        printf("No argument passed\n");

    return 0;
}
