/* Q7 : print the created thread ids  (compile with -pthread) */
#include <stdio.h>
#include <pthread.h>

static void *thread_fn(void *arg)
{
    printf("Thread %d : my id (pthread_self) = %lu\n", *(int *)arg, (unsigned long)pthread_self());
    return NULL;
}

int main(void)
{
    pthread_t t[3];
    int id[3] = {1, 2, 3}, i;

    printf("Main thread id = %lu\n", (unsigned long)pthread_self());
    for (i = 0; i < 3; i++) {
        pthread_create(&t[i], NULL, thread_fn, &id[i]);
        printf("Created thread %d, id returned by pthread_create = %lu\n", i + 1, (unsigned long)t[i]);
    }
    for (i = 0; i < 3; i++)
        pthread_join(t[i], NULL);
    return 0;
}
