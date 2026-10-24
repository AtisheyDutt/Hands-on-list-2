/* Q34c : client for the concurrent servers 34a / 34b.
 * Usage : ./34c [server-ip]   - type lines, the server echoes them back; Ctrl+D to quit */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5001

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    char line[256], buf[256];
    ssize_t n;

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, argc > 1 ? argv[1] : "127.0.0.1", &addr.sin_addr);
    if (connect(fd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("connect"); exit(1); }

    while (fgets(line, sizeof line, stdin)) {
        write(fd, line, strlen(line));
        n = read(fd, buf, sizeof buf - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("Echo : %s", buf);
    }
    close(fd);
    return 0;
}
