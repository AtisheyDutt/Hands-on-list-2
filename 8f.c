/* Q8f : set an interval timer using ITIMER_VIRTUAL (signal SIGVTALRM), interval = 1 sec 0 usec */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static volatile sig_atomic_t count = 0;

static void handler(int sig)
{
    const char msg[] = "SIGVTALRM received : ITIMER_VIRTUAL timer expired\n";
    (void)sig;
    write(1, msg, sizeof msg - 1);
    count++;
}

int main(void)
{
    struct itimerval t;
    t.it_value.tv_sec = 1;      t.it_value.tv_usec = 0;
    t.it_interval.tv_sec = 1;   t.it_interval.tv_usec = 0;

    signal(SIGVTALRM, handler);
    if (setitimer(ITIMER_VIRTUAL, &t, NULL) == -1) { perror("setitimer"); exit(1); }

    /* Run until the timer has fired 3 times */
    while (count < 3) {
        { volatile unsigned long i; for (i = 0; i < 100000000UL; i++); }
    }
    return 0;
}
