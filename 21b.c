/* Q21b : FIFO two way communication - PROGRAM B (run second). */
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
    int rfd, wfd;
    ssize_t n;

    if ((mkfifo(FIFO_AB, 0666) == -1 && errno != EEXIST) ||
        (mkfifo(FIFO_BA, 0666) == -1 && errno != EEXIST)) { perror("mkfifo"); exit(1); }

    rfd = open(FIFO_AB, O_RDONLY);
    wfd = open(FIFO_BA, O_WRONLY);

    n = read(rfd, buf, sizeof buf);
    if (n > 0) printf("B received : %s", buf);

    printf("B : enter reply for A : ");
    fgets(buf, sizeof buf, stdin);
    write(wfd, buf, strlen(buf) + 1);

    close(rfd); close(wfd);
    return 0;
}
