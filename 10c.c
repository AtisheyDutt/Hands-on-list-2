/* Q10c : catch SIGFPE using sigaction() */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void handler(int sig)
{
    printf("Caught signal %d (SIGFPE)\n", sig);
    exit(1);
}

int main(void)
{
    struct sigaction sa;
    volatile int a = 5, b = 0, c;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGFPE, &sa, NULL);

    c = a / b;
    printf("%d\n", c);
    return 0;
}
