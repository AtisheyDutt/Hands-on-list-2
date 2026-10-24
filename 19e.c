/* Q19e : create a FIFO using the mkfifo library function */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    if (mkfifo("fifo_mkfifo", 0666) == -1) { perror("mkfifo"); return 1; }
    printf("FIFO 'fifo_mkfifo' created using mkfifo()\n");
    return 0;
}
