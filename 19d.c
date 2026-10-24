/* Q19d : create a FIFO using the mknod system call */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    if (mknod("fifo_mknod", S_IFIFO | 0666, 0) == -1) { perror("mknod"); return 1; }
    printf("FIFO 'fifo_mknod' created using mknod()\n");
    return 0;
}
