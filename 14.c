/* Q14 : create a pipe, write to it, read from it and display */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    char buf[100];
    const char *msg = "Hello through the pipe!";
    ssize_t n;

    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    write(fd[1], msg, strlen(msg));          /* write end */
    n = read(fd[0], buf, sizeof buf - 1);    /* read end  */
    buf[n] = '\0';

    printf("Read from pipe : %s\n", buf);
    close(fd[0]); close(fd[1]);
    return 0;
}
