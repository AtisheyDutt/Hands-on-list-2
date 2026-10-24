/* Q22 : wait up to 10 seconds for data on a FIFO using select().
 * Test :  ./22      (in terminal 1)   and   echo hi > myfifo22   (in terminal 2) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>

#define FIFO "myfifo22"

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    char buf[100];
    int fd, ret;
    ssize_t n;

    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) { perror("mkfifo"); exit(1); }

    fd = open(FIFO, O_RDWR);                   /* O_RDWR : open does not block, no premature EOF */
    if (fd == -1) { perror("open"); exit(1); }

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    printf("Waiting up to 10 seconds for data in FIFO '%s' ...\n", FIFO);
    ret = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (ret == -1) perror("select");
    else if (ret == 0) printf("Timeout : no data within 10 seconds\n");
    else {
        n = read(fd, buf, sizeof buf - 1);
        buf[n] = '\0';
        printf("Data available : %s", buf);
    }
    close(fd);
    unlink(FIFO);
    return 0;
}
