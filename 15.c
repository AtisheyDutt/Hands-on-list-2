/* Q15 : send data from parent to child using a pipe */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    char buf[100];
    ssize_t n;
    pid_t pid;

    if (pipe(fd) == -1) { perror("pipe"); exit(1); }
    pid = fork();

    if (pid == 0) {                          /* child : reader */
        close(fd[1]);
        n = read(fd[0], buf, sizeof buf - 1);
        buf[n] = '\0';
        printf("Child received : %s\n", buf);
        close(fd[0]);
    } else {                                 /* parent : writer */
        const char *msg = "Message from parent";
        close(fd[0]);
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
