/* Q8a : catch SIGSEGV using signal() */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void handler(int sig)
{
    printf("Caught signal %d (SIGSEGV) - invalid memory access\n", sig);
    exit(1);            /* returning would re-execute the faulting instruction forever */
}

int main(void)
{
    int *p = NULL;
    signal(SIGSEGV, handler);
    *p = 10;            /* generates SIGSEGV */
    return 0;
}
