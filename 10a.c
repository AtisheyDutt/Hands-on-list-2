/* Q10a : catch SIGSEGV using sigaction() */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void handler(int sig)
{
    printf("Caught signal %d (SIGSEGV)\n", sig);
    exit(1);
}

int main(void)
{
    struct sigaction sa;
    int *p = NULL;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);

    *p = 10;
    return 0;
}
