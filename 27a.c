/* Q27a : receive a message from the queue with 0 as flag (blocks until a message arrives) */
#include <stdio.h>
#include <stdlib.h>
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
    printf("Waiting for a message (flag = 0, blocking) ...\n");
    if (msgrcv(msqid, &m, sizeof m.mtext, 0, 0) == -1) { perror("msgrcv"); exit(1); }
    printf("Received : %s\n", m.mtext);
    return 0;
}
