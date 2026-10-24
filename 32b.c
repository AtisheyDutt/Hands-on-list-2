/* Q32b : protect shared memory from concurrent write access using a binary semaphore */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
    int shmid = shmget(IPC_PRIVATE, 256, IPC_CREAT | 0666);
    union semun arg;
    char *shm;
    int i;

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);
    shm = (char *)shmat(shmid, NULL, 0);
    shm[0] = '\0';

    for (i = 1; i <= 3; i++) {
        if (fork() == 0) {                          /* writer process */
            char line[64];
            sem_op(semid, -1);                      /* lock */
            snprintf(line, sizeof line, "[writer %d, pid %d] ", i, getpid());
            printf("Writer %d entered critical section\n", i);
            strcat(shm, line);                      /* write to shared memory */
            sleep(1);
            printf("Writer %d leaving critical section\n", i);
            sem_op(semid, +1);                      /* unlock */
            shmdt(shm);
            exit(0);
        }
    }
    for (i = 0; i < 3; i++) wait(NULL);

    printf("Shared memory content : %s\n", shm);
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
