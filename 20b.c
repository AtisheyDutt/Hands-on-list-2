/* Q20b : FIFO one way communication - READER.  Run 20a (writer) in another terminal */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO "fifo_oneway"

int main(void)
{
    char buf[100];
    int fd;

    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) { perror("mkfifo"); exit(1); }

    fd = open(FIFO, O_RDONLY);                 /* blocks until writer opens */
    read(fd, buf, sizeof buf);
    printf("Reader received : %s", buf);
    close(fd);
    return 0;
}
