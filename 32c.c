/* Q32c : protect two pseudo resources using a counting semaphore (initial value 2).
 * Five processes compete; only two can use the resources at a time. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

static void sem_op(int semid, int delta)
{
    struct sembuf sb = {0, (short)delta, 0};
    semop(semid, &sb, 1);
}

int main(void)
{
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    union semun arg;
    int i;

    arg.val = 2;                                    /* two resources */
    semctl(semid, 0, SETVAL, arg);

    for (i = 1; i <= 5; i++) {
        if (fork() == 0) {
            printf("Process %d : waiting for a resource\n", i);
            sem_op(semid, -1);                      /* acquire */
            printf("Process %d : got a resource  (free now = %d)\n", i, semctl(semid, 0, GETVAL));
            sleep(2);                               /* use the resource */
            printf("Process %d : releasing the resource\n", i);
            sem_op(semid, +1);                      /* release */
            exit(0);
        }
    }
    for (i = 0; i < 5; i++) wait(NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
