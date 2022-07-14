#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void show_handler(int sig)
{
    printf("I got signal %d\n", sig);
}

int main()
{
    int i = 0;
    struct sigaction act, oldact;
    act.sa_handler = show_handler;
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;
    printf("SIGINT signal:  %d\n", SIGINT);
    printf("SIGCONT signal:  %d\n", SIGCONT);
    printf("SIGKILL signal:  %d\n", SIGKILL);
    printf("SIGTERM signal:  %d\n", SIGTERM);
    printf("SIGQUIT signal:  %d\n", SIGQUIT);
    sigaction(SIGINT, &act, &oldact);
    sigaction(SIGCONT, &act, &oldact);
    sigaction(SIGKILL, &act, &oldact);
    sigaction(SIGTERM, &act, &oldact);
    sigaction(SIGQUIT, &act, &oldact);
    while(1) {
        sleep(1);
        i++;
    }
    return 0;
}
