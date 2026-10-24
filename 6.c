/* Q6 : create three threads  (compile with -pthread) */
#include <stdio.h>
#include <pthread.h>

static void *thread_fn(void *arg)
{
    printf("Hello from thread %d\n", *(int *)arg);
    return NULL;
}

int main(void)
{
    pthread_t t[3];
    int id[3] = {1, 2, 3}, i;

    for (i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, thread_fn, &id[i]);
    for (i = 0; i < 3; i++)
        pthread_join(t[i], NULL);
    return 0;
}
