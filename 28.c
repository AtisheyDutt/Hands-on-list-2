/* Q28 : change the permission of an existing message queue (msqid_ds + IPC_SET) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key = ftok(".", 'q');
    int msqid = msgget(key, 0);
    struct msqid_ds ds;

    if (msqid == -1) { perror("msgget (create the queue first with ./24)"); exit(1); }

    msgctl(msqid, IPC_STAT, &ds);
    printf("Old permission : %o\n", ds.msg_perm.mode & 0777);

    ds.msg_perm.mode = 0600;                       /* rw------- */
    if (msgctl(msqid, IPC_SET, &ds) == -1) { perror("msgctl IPC_SET"); exit(1); }

    msgctl(msqid, IPC_STAT, &ds);
    printf("New permission : %o\n", ds.msg_perm.mode & 0777);
    return 0;
}
