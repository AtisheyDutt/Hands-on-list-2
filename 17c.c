/* Q17c : ls -l | wc  using fcntl (F_DUPFD) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    if (fork() == 0) {
        close(1);
        fcntl(fd[1], F_DUPFD, 1);      /* duplicate to lowest free fd >= 1  => 1 */
        close(fd[0]); close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls"); exit(1);
    }
    if (fork() == 0) {
        close(0);
        fcntl(fd[0], F_DUPFD, 0);      /* duplicate to lowest free fd >= 0  => 0 */
        close(fd[0]); close(fd[1]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc"); exit(1);
    }
    close(fd[0]); close(fd[1]);
    wait(NULL); wait(NULL);
    return 0;
}
