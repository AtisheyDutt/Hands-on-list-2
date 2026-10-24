/* Q16 : two way communication between parent and child using two pipes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int p2c[2], c2p[2];
    char buf[100];
    ssize_t n;
    pid_t pid;

    if (pipe(p2c) == -1 || pipe(c2p) == -1) { perror("pipe"); exit(1); }
    pid = fork();

    if (pid == 0) {                                   /* child */
        close(p2c[1]); close(c2p[0]);
        n = read(p2c[0], buf, sizeof buf - 1);
        buf[n] = '\0';
        printf("Child  received : %s\n", buf);
        write(c2p[1], "Hi parent, child here", 21);
        close(p2c[0]); close(c2p[1]);
    } else {                                          /* parent */
        close(p2c[0]); close(c2p[1]);
        write(p2c[1], "Hello child, parent here", 24);
        n = read(c2p[0], buf, sizeof buf - 1);
        buf[n] = '\0';
        printf("Parent received : %s\n", buf);
        close(p2c[1]); close(c2p[0]);
        wait(NULL);
    }
    return 0;
}
