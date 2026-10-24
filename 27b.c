/* Q27b : receive a message with IPC_NOWAIT (returns immediately with ENOMSG if queue is empty) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf_t { long mtype; char mtext[100]; };

int main(void)
{
    key_t key = ftok(".", 'q');
    int msqid = msgget(key, IPC_CREAT | 0666);
    struct msgbuf_t m;

    if (msqid == -1) { perror("msgget"); exit(1); }
    if (msgrcv(msqid, &m, sizeof m.mtext, 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) printf("No message in the queue (IPC_NOWAIT)\n");
        else perror("msgrcv");
        exit(1);
    }
    printf("Received : %s\n", m.mtext);
    return 0;
}
