/* Q33b : socket communication between two machines - CLIENT.
 * Usage : ./33b <server-ip>      (default 127.0.0.1) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000

int main(int argc, char *argv[])
{
    int fd;
    struct sockaddr_in addr;
    char buf[100];
    ssize_t n;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) { perror("socket"); exit(1); }

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, argc > 1 ? argv[1] : "127.0.0.1", &addr.sin_addr) <= 0) { fprintf(stderr, "bad address\n"); exit(1); }

    if (connect(fd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("connect"); exit(1); }

    write(fd, "Hello from client", 17);
    n = read(fd, buf, sizeof buf - 1);
    buf[n] = '\0';
    printf("Client received : %s\n", buf);

    close(fd);
    return 0;
}
