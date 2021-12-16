#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

#include <stdio.h>

// Il faudrait regarder `nouveau les fonctions autoorrisées

void    printMsgHandler(int signum, siginfo_t *info, void *unused)
{
    (void)unused;
    (void)info;
    printf("YOLO I MADE IT\n");
    printf("signum: %d\n", signum);
    return ;
}

int main()
{
    pid_t   pid_server;
    pid_server = getpid();

    printf("Hi I'm server and this is my PID : %d\n\n", pid_server);

    struct sigaction	s;

	s.sa_sigaction = printMsgHandler;
    s.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &s, NULL);
    pause();
    

    return (0);


} 