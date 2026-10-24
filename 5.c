/* Q5 : print system limitations using sysconf */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("a. Max length of arguments to exec family : %ld\n", sysconf(_SC_ARG_MAX));
    printf("b. Max simultaneous processes per user id : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Clock ticks (jiffies) per second       : %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. Max number of open files               : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. Size of a page                         : %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("f. Total pages in physical memory         : %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. Currently available pages in memory    : %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}
