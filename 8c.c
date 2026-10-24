/* Q8c : catch SIGFPE using signal() */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void handler(int sig)
{
    printf("Caught signal %d (SIGFPE) - arithmetic exception\n", sig);
    exit(1);
}

int main(void)
{
    volatile int a = 10, b = 0, c;
    signal(SIGFPE, handler);
    c = a / b;          /* integer divide by zero -> SIGFPE */
    printf("%d\n", c);
    return 0;
}
