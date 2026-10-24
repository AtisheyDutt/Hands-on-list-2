/* Q17a : ls -l | wc  using dup */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    if (fork() == 0) {                 /* child 1 : ls -l, stdout -> pipe */
        close(1);                      /* free fd 1 */
        dup(fd[1]);                    /* dup returns lowest free fd = 1 */
        close(fd[0]); close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls"); exit(1);
    }
    if (fork() == 0) {                 /* child 2 : wc, stdin <- pipe */
        close(0);
        dup(fd[0]);                    /* becomes fd 0 */
        close(fd[0]); close(fd[1]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc"); exit(1);
    }
    close(fd[0]); close(fd[1]);
    wait(NULL); wait(NULL);
    return 0;
}
