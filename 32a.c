/* Q32a : ticket number creation protected by a semaphore.
 * Run in two terminals at the same time: the second one waits until the first
 * one presses ENTER (leaves the critical section). */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

static void sem_op(int semid, int delta)
{
    struct sembuf sb = {0, (short)delta, 0};
    if (semop(semid, &sb, 1) == -1) { perror("semop"); exit(1); }
}

int main(void)
{
    key_t key = ftok(".", 'a');
    int semid, fd, ticket;
    union semun arg;

    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid >= 0) { arg.val = 1; semctl(semid, 0, SETVAL, arg); }   /* first creator initialises */
    else semid = semget(key, 1, 0666);

    fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);
    if (lseek(fd, 0, SEEK_END) == 0) { ticket = 100; write(fd, &ticket, sizeof ticket); }

    printf("Before critical section\n");
    sem_op(semid, -1);                            /* lock  (P / wait)   */
    printf("Inside critical section\n");

    lseek(fd, 0, SEEK_SET);
    read(fd, &ticket, sizeof ticket);
    ticket++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket, sizeof ticket);
    printf("Your ticket number is : %d\n", ticket);

    printf("Press ENTER to leave the critical section ...\n");
    getchar();
    sem_op(semid, +1);                            /* unlock (V / signal) */
    printf("Left critical section\n");
    close(fd);
    return 0;
}
