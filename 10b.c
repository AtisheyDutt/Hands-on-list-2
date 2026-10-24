/* Q10b : catch SIGINT using sigaction() */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig)
{
    printf("\nCaught signal %d (SIGINT)\n", sig);
    exit(0);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C ...\n");
    while (1) pause();
    return 0;
}
