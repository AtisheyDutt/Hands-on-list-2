/* Q1a : set an interval timer using ITIMER_REAL (signal SIGALRM), interval = 10 sec 10 usec */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static volatile sig_atomic_t count = 0;

static void handler(int sig)
{
    const char msg[] = "SIGALRM received : ITIMER_REAL timer expired\n";
    (void)sig;
    write(1, msg, sizeof msg - 1);
    count++;
}

int main(void)
{
    struct itimerval t;
    t.it_value.tv_sec = 10;      t.it_value.tv_usec = 10;
    t.it_interval.tv_sec = 10;   t.it_interval.tv_usec = 10;

    signal(SIGALRM, handler);
    if (setitimer(ITIMER_REAL, &t, NULL) == -1) { perror("setitimer"); exit(1); }

    /* Run until the timer has fired 3 times */
    while (count < 3) {
        pause();
    }
    return 0;
}
