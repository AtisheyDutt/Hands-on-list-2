/* Q34a : concurrent (echo) server using fork - one child process per client.
 * Test with :  ./34a   and in other terminals  ./34c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5001

static void serve(int cfd)
{
    char buf[256];
    ssize_t n;
    while ((n = read(cfd, buf, sizeof buf)) > 0)
        write(cfd, buf, n);                        /* echo back */
}

int main(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);
    int sfd, cfd, opt = 1;
    struct sockaddr_in addr;

    signal(SIGCHLD, SIG_IGN);                      /* do not leave zombies */

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if (bind(sfd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("bind"); exit(1); }
    listen(sfd, 10);
    printf("fork server listening on port %d\n", PORT);

    while (1) {
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1) continue;
        if (fork() == 0) {                         /* child */
            close(sfd);
            printf("Child %d serving a client\n", getpid());
            serve(cfd);
            close(cfd);
            exit(0);
        }
        close(cfd);                                /* parent */
    }
    return 0;
}
