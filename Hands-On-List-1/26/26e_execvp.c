/*
==========================================================================================================================
Name : 26e_execvp.c
Author : Hetul Mehta
Description : C program to execute ls -Rl using execvp.
Date: 18th Sept, 2026.
==========================================================================================================================
*/

#include <unistd.h>

int main() {

    char *args[] = {"ls", "-Rl", NULL};

    execvp("ls", args);

    return 0;
}

/*
==========================================================================================================================
-rwxrwxr-x  1 hetul hetul 70456 Sep 18 11:09 26a*
-rw-rw-r--  1 hetul hetul   464 Sep 18 11:09 26a_execl.c
-rwxrwxr-x  1 hetul hetul 70456 Sep 18 11:09 26b*
-rw-rw-r--  1 hetul hetul   462 Sep 18 11:09 26b_execlp.c
-rwxrwxr-x  1 hetul hetul 70560 Sep 18 11:09 26c*
-rw-rw-r--  1 hetul hetul   499 Sep 18 11:09 26c_execle.c
-rwxrwxr-x  1 hetul hetul 70608 Sep 18 11:09 26d*
-rw-rw-r--  1 hetul hetul   492 Sep 18 11:09 26d_execv.c
-rwxrwxr-x  1 hetul hetul 70608 Sep 18 11:09 26e*
-rw-rw-r--  1 hetul hetul   491 Sep 18 11:09 26e_execvp.c
==========================================================================================================================
*/