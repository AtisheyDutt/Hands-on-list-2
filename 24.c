/* Q24 : create a message queue and print the key and the message queue id */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    key_t key;
    int msqid;

    key = ftok(".", 'q');
    if (key == -1) { perror("ftok"); exit(1); }

    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); exit(1); }

    printf("Key              : %d (0x%x)\n", key, key);
    printf("Message queue id : %d\n", msqid);
    return 0;
}
