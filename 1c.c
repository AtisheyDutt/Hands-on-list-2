/* Q1c : set an interval timer using ITIMER_PROF (signal SIGPROF), interval = 10 sec 10 usec */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static volatile sig_atomic_t count = 0;

static void handler(int sig)
{
    const char msg[] = "SIGPROF received : ITIMER_PROF timer expired\n";
    (void)sig;
    write(1, msg, sizeof msg - 1);
    count++;
}

int main(void)
{
    struct itimerval t;
    t.it_value.tv_sec = 10;      t.it_value.tv_usec = 10;
    t.it_interval.tv_sec = 10;   t.it_interval.tv_usec = 10;

    signal(SIGPROF, handler);
    if (setitimer(ITIMER_PROF, &t, NULL) == -1) { perror("setitimer"); exit(1); }

    /* Run until the timer has fired 3 times */
    while (count < 3) {
        { volatile unsigned long i; for (i = 0; i < 100000000UL; i++); }
    }
    return 0;
}
