/* Q23 : maximum number of files that can be opened in a process, and size of a pipe (circular buffer) */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>

int main(void)
{
    struct rlimit rl;
    int fd[2];
    long count = 0;
    char c = 'x';

    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Max open files (sysconf)          : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Max open files (RLIMIT_NOFILE)    : soft = %lu, hard = %lu\n",
           (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);

    printf("Atomic pipe write size (PIPE_BUF) : %ld bytes\n", fpathconf(STDIN_FILENO, _PC_PIPE_BUF));

    pipe(fd);
#ifdef F_GETPIPE_SZ
    printf("Pipe capacity (F_GETPIPE_SZ)      : %d bytes\n", fcntl(fd[1], F_GETPIPE_SZ));
#endif
    /* measure it : fill the pipe without a reader until it is full */
    fcntl(fd[1], F_SETFL, O_NONBLOCK);
    while (write(fd[1], &c, 1) == 1) count++;
    printf("Pipe size by filling it           : %ld bytes\n", count);
    return 0;
}
