/* Q30 : shared memory - create, write, read-only attach (try to overwrite), detach, remove */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    key_t key = ftok(".", 's');
    int shmid;
    char *ptr;
    pid_t pid;
    int status;

    /* create */
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); exit(1); }
    printf("Shared memory created, id = %d\n", shmid);

    /* a. attach read/write and write some data */
    ptr = (char *)shmat(shmid, NULL, 0);
    if (ptr == (char *)-1) { perror("shmat"); exit(1); }
    strcpy(ptr, "Hello shared memory");
    printf("a. Written : %s\n", ptr);

    /* b. attach read only (SHM_RDONLY) and try to overwrite.
       The write raises SIGSEGV, so do it in a child process to keep the parent alive. */
    fflush(stdout);                                /* avoid duplicated buffered output in the child */
    pid = fork();
    if (pid == 0) {
        char *ro = (char *)shmat(shmid, NULL, SHM_RDONLY);
        printf("b. Read-only attach, data = %s\n", ro);
        printf("   Trying to overwrite ...\n");
        fflush(stdout);
        strcpy(ro, "overwritten");                 /* -> SIGSEGV */
        printf("   Overwrite succeeded (unexpected)\n");
        exit(0);
    }
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        printf("   Child killed by signal %d (SIGSEGV) : cannot overwrite a read-only attachment\n", WTERMSIG(status));

    printf("   Data still : %s\n", ptr);

    /* c. detach */
    shmdt(ptr);
    printf("c. Detached\n");

    /* d. remove */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl"); exit(1); }
    printf("d. Shared memory removed\n");
    return 0;
}
