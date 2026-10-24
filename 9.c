/* Q9 : ignore SIGINT, then reset it to the default action - signal() */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is ignored for 5 seconds - try Ctrl+C (nothing happens)\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT reset to default action - press Ctrl+C now to terminate\n");
    sleep(10);
    printf("Finished without Ctrl+C\n");
    return 0;
}
