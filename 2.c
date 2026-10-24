/* Q2 : print the system resource limits using getrlimit */
#include <stdio.h>
#include <sys/resource.h>

#define SHOW(r) show(#r, r)

static void show(const char *name, int res)
{
    struct rlimit rl;
    if (getrlimit(res, &rl) == -1) { perror(name); return; }
    printf("%-18s soft = ", name);
    if (rl.rlim_cur == RLIM_INFINITY) printf("%-12s", "unlimited");
    else printf("%-12lu", (unsigned long)rl.rlim_cur);
    printf(" hard = ");
    if (rl.rlim_max == RLIM_INFINITY) printf("unlimited\n");
    else printf("%lu\n", (unsigned long)rl.rlim_max);
}

int main(void)
{
    SHOW(RLIMIT_CPU);      SHOW(RLIMIT_FSIZE);   SHOW(RLIMIT_DATA);
    SHOW(RLIMIT_STACK);    SHOW(RLIMIT_CORE);    SHOW(RLIMIT_RSS);
    SHOW(RLIMIT_NPROC);    SHOW(RLIMIT_NOFILE);  SHOW(RLIMIT_MEMLOCK);
    SHOW(RLIMIT_AS);       SHOW(RLIMIT_LOCKS);   SHOW(RLIMIT_SIGPENDING);
    SHOW(RLIMIT_MSGQUEUE); SHOW(RLIMIT_NICE);    SHOW(RLIMIT_RTPRIO);
    SHOW(RLIMIT_RTTIME);
    return 0;
}
