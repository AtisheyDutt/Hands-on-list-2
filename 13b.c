/* Q13b : send SIGSTOP to the process whose pid is given (usage: ./13b <pid>) */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if (argc > 1) pid = (pid_t)atoi(argv[1]);
    else { printf("Enter pid of 13a : "); scanf("%d", &pid); }

    if (kill(pid, SIGSTOP) == -1) { perror("kill"); return 1; }
    printf("SIGSTOP sent to %d. The target is stopped (not caught). Use 'kill -CONT %d' to resume.\n", pid, pid);
    return 0;
}
