/* Q8b : catch SIGINT (Ctrl+C) using signal() */
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
    signal(SIGINT, handler);
    printf("Press Ctrl+C ...\n");
    while (1) pause();
    return 0;
}
