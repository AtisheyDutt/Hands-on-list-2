/* Q32d : remove the created semaphores (those made by 31a, 31b and 32a) */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{
    const char ids[] = {'a', 'b', 'c'};             /* ftok project ids used by 32a, 31a, 31b */
    int i;

    for (i = 0; i < 3; i++) {
        key_t key = ftok(".", ids[i]);
        int semid = semget(key, 1, 0);
        if (semid == -1) { printf("Semaphore for id '%c' does not exist\n", ids[i]); continue; }
        if (semctl(semid, 0, IPC_RMID) == 0)
            printf("Semaphore id %d (project id '%c') removed\n", semid, ids[i]);
        else perror("semctl IPC_RMID");
    }
    return 0;
}
