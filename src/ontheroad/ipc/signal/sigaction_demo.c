#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ouch(int sig)
{
    printf("\nOUCH! Got signal [%d]\n", sig);
}

int main()
{
    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;

    sigaction(SIGINT, &act, 0);

    while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}

    return 0;
}
