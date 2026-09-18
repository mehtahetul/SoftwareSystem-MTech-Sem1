#include<stdio.h>
#include<unistd.h>

int main(){
	if(symlink("demo.txt","softlink_syscall.txt") == -1)
	{
		perror("symlink");
		return 1;
	}

	printf("Softlink created succesfully. \n");
	return 0;
}
