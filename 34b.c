/* Q34b : concurrent (echo) server using pthread_create - one thread per client.
 * Compile with -pthread.  Test with ./34b and several ./34c (change PORT if needed). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 5001

static void *serve(void *arg)
{
    int cfd = *(int *)arg;
    char buf[256];
    ssize_t n;

    free(arg);
    printf("Thread %lu serving a client\n", (unsigned long)pthread_self());
    while ((n = read(cfd, buf, sizeof buf)) > 0)
        write(cfd, buf, n);
    close(cfd);
    return NULL;
}

int main(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);
    int sfd, opt = 1;
    struct sockaddr_in addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if (bind(sfd, (struct sockaddr *)&addr, sizeof addr) == -1) { perror("bind"); exit(1); }
    listen(sfd, 10);
    printf("pthread server listening on port %d\n", PORT);

    while (1) {
        int *cfd = malloc(sizeof(int));
        pthread_t t;
        *cfd = accept(sfd, NULL, NULL);
        if (*cfd == -1) { free(cfd); continue; }
        pthread_create(&t, NULL, serve, cfd);
        pthread_detach(t);
    }
    return 0;
}
