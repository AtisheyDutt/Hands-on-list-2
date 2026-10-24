/* Q26 : send messages to the message queue.  Check afterwards with:  ipcs -q */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf_t { long mtype; char mtext[100]; };

int main(void)
{
    key_t key = ftok(".", 'q');
    int msqid = msgget(key, IPC_CREAT | 0666);
    struct msgbuf_t m;
    int i, n;

    if (msqid == -1) { perror("msgget"); exit(1); }

    printf("How many messages to send ? ");
    scanf("%d", &n);
    getchar();
    for (i = 1; i <= n; i++) {
        printf("Message %d : ", i);
        fgets(m.mtext, sizeof m.mtext, stdin);
        m.mtext[strcspn(m.mtext, "\n")] = '\0';
        m.mtype = 1;
        if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1) { perror("msgsnd"); exit(1); }
    }
    printf("%d message(s) sent. Run 'ipcs -q' to verify.\n", n);
    return 0;
}
