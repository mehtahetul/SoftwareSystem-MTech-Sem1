#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    if (mknod("myfifo_mknod", S_IFIFO | 0666, 0) == -1)
    {
        perror("mknod");
        return 1;
    }

    printf("FIFO created successfully using mknod().\n");

    return 0;
}
