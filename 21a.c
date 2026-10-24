/* Q21a : FIFO two way communication - PROGRAM A (run first).  Uses two FIFOs. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_AB "fifo_a_to_b"
#define FIFO_BA "fifo_b_to_a"

int main(void)
{
    char buf[100];
    int wfd, rfd;
    ssize_t n;

    if ((mkfifo(FIFO_AB, 0666) == -1 && errno != EEXIST) ||
        (mkfifo(FIFO_BA, 0666) == -1 && errno != EEXIST)) { perror("mkfifo"); exit(1); }

    wfd = open(FIFO_AB, O_WRONLY);             /* same open order in both programs avoids deadlock */
    rfd = open(FIFO_BA, O_RDONLY);

    printf("A : enter message for B : ");
    fgets(buf, sizeof buf, stdin);
    write(wfd, buf, strlen(buf) + 1);

    n = read(rfd, buf, sizeof buf);
    if (n > 0) printf("A received : %s", buf);

    close(wfd); close(rfd);
    return 0;
}
