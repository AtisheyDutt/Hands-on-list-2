/* Q8d : catch SIGALRM using the alarm() system call */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig)
{
    printf("Caught signal %d (SIGALRM) - alarm expired\n", sig);
    exit(0);
}

int main(void)
{
    signal(SIGALRM, handler);
    alarm(3);
    printf("Alarm set for 3 seconds ...\n");
    while (1) pause();
    return 0;
}
