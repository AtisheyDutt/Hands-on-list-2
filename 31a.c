/* Q31a : create a binary semaphore and initialise it to 1 (System V) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main(void)
{
    key_t key = ftok(".", 'b');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    union semun arg;

    if (semid == -1) { perror("semget"); exit(1); }
    arg.val = 1;                                  /* binary : 0 or 1 */
    if (semctl(semid, 0, SETVAL, arg) == -1) { perror("semctl"); exit(1); }

    printf("Binary semaphore created, id = %d, value = %d\n", semid, semctl(semid, 0, GETVAL));
    printf("Remove it with : ipcrm -s %d\n", semid);
    return 0;
}
