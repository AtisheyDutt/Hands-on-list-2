/* Q4 : time taken by 100 getppid() calls, measured with the time stamp counter (x86 rdtsc) */
#include <stdio.h>
#include <unistd.h>

static inline unsigned long long rdtsc(void)
{
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main(void)
{
    unsigned long long start, end;
    int i;

    start = rdtsc();
    for (i = 0; i < 100; i++)
        getppid();
    end = rdtsc();

    printf("Time taken for 100 getppid() calls : %llu CPU cycles\n", end - start);
    printf("Average per call                   : %llu CPU cycles\n", (end - start) / 100);
    return 0;
}
