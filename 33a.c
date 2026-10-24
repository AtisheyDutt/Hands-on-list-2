/* Q33a : socket communication between two machines - SERVER.
 * Usage : ./33a      (then run ./33b <server-ip> on the other machine) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5000

int main(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);
    int sfd, cfd;
    struct sockaddr_in addr;
    char buf[100];
    ssize_t n;
    int opt = 1;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) { perror("socket"); exit(1); }
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(sfd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("bind"); exit(1); }
    listen(sfd, 5);
    printf("Server waiting on port %d ...\n", PORT);

    cfd = accept(sfd, NULL, NULL);
    if (cfd == -1) { perror("accept"); exit(1); }

    n = read(cfd, buf, sizeof buf - 1);
    buf[n] = '\0';
    printf("Server received : %s\n", buf);
    write(cfd, "Hello from server", 17);

    close(cfd); close(sfd);
    return 0;
}
