/* Q25 : print information of a message queue (msqid_ds and ipc_perm) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key = ftok(".", 'q');
    int msqid = msgget(key, IPC_CREAT | 0666);
    struct msqid_ds ds;

    if (msqid == -1) { perror("msgget"); exit(1); }
    if (msgctl(msqid, IPC_STAT, &ds) == -1) { perror("msgctl"); exit(1); }

    printf("a. Access permission          : %o\n", ds.msg_perm.mode & 0777);
    printf("b. uid = %d, gid = %d\n", ds.msg_perm.uid, ds.msg_perm.gid);
    printf("c. Time of last msgsnd        : %s", ds.msg_stime ? ctime(&ds.msg_stime) : "not yet\n");
    printf("   Time of last msgrcv        : %s", ds.msg_rtime ? ctime(&ds.msg_rtime) : "not yet\n");
    printf("d. Time of last change        : %s", ctime(&ds.msg_ctime));
    printf("e. Size of queue (bytes used) : %lu\n", (unsigned long)ds.__msg_cbytes);
    printf("f. Number of messages         : %lu\n", (unsigned long)ds.msg_qnum);
    printf("g. Max bytes allowed          : %lu\n", (unsigned long)ds.msg_qbytes);
    printf("h. pid of last msgsnd         : %d\n", ds.msg_lspid);
    printf("   pid of last msgrcv         : %d\n", ds.msg_lrpid);
    return 0;
}
