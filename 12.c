/* Q12 : create an orphan process; the child kills its parent with SIGKILL */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {                                   /* child */
        printf("Child  : pid = %d, parent pid = %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL);                     /* kill the parent */
        sleep(2);                                     /* give init/systemd time to adopt us */
        printf("Child  : orphan now, new parent pid = %d (init/systemd/subreaper)\n", getppid());
    } else {                                          /* parent */
        printf("Parent : pid = %d, waiting to be killed ...\n", getpid());
        sleep(20);
        printf("Parent : (never printed)\n");
    }
    return 0;
}
