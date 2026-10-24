/* Q18 : count the directories in the pwd :  ls -l | grep ^d | wc   (only dup2) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int p1[2], p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1) { perror("pipe"); exit(1); }

    if (fork() == 0) {                         /* ls -l  -> p1 */
        dup2(p1[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("ls"); exit(1);
    }
    if (fork() == 0) {                         /* grep ^d : p1 -> p2 */
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", (char *)NULL);
        perror("grep"); exit(1);
    }
    if (fork() == 0) {                         /* wc : p2 -> terminal */
        dup2(p2[0], 0);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("wc", "wc", (char *)NULL);
        perror("wc"); exit(1);
    }
    close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
