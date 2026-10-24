/* Q13a : try to catch SIGSTOP.  Run this first, then run 13b with the printed pid.
 * Result : SIGSTOP can NOT be caught, blocked or ignored - signal()/sigaction() fail
 * with EINVAL and the process is simply stopped by the kernel. */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig)
{
    printf("Caught signal %d\n", sig);      /* never executed for SIGSTOP */
}

int main(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);       /* line buffered so output shows even when redirected */
    struct sigaction sa;

    if (signal(SIGSTOP, handler) == SIG_ERR)
        perror("signal(SIGSTOP)");

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGSTOP, &sa, NULL) == -1)
        perror("sigaction(SIGSTOP)");

    printf("pid = %d  - waiting for SIGSTOP (run ./13b %d)\n", getpid(), getpid());
    while (1) { printf("running ...\n"); sleep(2); }
    return 0;
}
