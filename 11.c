/* Q11 : ignore SIGINT, then reset to default action - sigaction() */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;                 /* ignore */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT ignored for 5 seconds - try Ctrl+C\n");
    sleep(5);

    sa.sa_handler = SIG_DFL;                 /* default action */
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT reset to default - press Ctrl+C to terminate\n");
    sleep(10);
    printf("Finished without Ctrl+C\n");
    return 0;
}
