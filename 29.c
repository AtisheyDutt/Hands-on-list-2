/* Q29 : remove the message queue */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key = ftok(".", 'q');
    int msqid = msgget(key, 0);

    if (msqid == -1) { perror("msgget"); exit(1); }
    if (msgctl(msqid, IPC_RMID, NULL) == -1) { perror("msgctl IPC_RMID"); exit(1); }
    printf("Message queue %d removed\n", msqid);
    return 0;
}
