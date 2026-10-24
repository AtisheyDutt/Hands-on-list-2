/* Q20a : FIFO one way communication - WRITER.  Run 20b (reader) in another terminal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO "fifo_oneway"

int main(void)
{
    char msg[100];
    int fd;

    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) { perror("mkfifo"); exit(1); }

    printf("Writer : waiting for a reader ...\n");
    fd = open(FIFO, O_WRONLY);                 /* blocks until reader opens */
    printf("Enter message : ");
    fgets(msg, sizeof msg, stdin);
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    return 0;
}
