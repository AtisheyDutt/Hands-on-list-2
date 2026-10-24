/* Q3 : set a system resource limit (RLIMIT_NOFILE) using setrlimit */
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
    struct rlimit rl;

    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Before : soft = %lu, hard = %lu\n", (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);

    rl.rlim_cur = 512;                 /* new soft limit (must be <= hard limit) */
    if (setrlimit(RLIMIT_NOFILE, &rl) == -1) { perror("setrlimit"); exit(1); }

    getrlimit(RLIMIT_NOFILE, &rl);
    printf("After  : soft = %lu, hard = %lu\n", (unsigned long)rl.rlim_cur, (unsigned long)rl.rlim_max);
    return 0;
}
