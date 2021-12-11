#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

#include <stdio.h>

// struct sigaction
// {
//     void     (*sa_handler) (int);
//     void     (*sa_sigaction) (int, siginfo_t *, void *);
//     sigset_t   sa_mask;
//     int        sa_flags;
//     void     (*sa_restorer) (void);
// };
 
void    printMsgHandler(int signum)
{
    printf("YOLO I MADE IT\n");
    return ;
}
int     main(int ac, char **av)
{
    if (ac != 3)
        return (0);
    printf("Client speaking, I am receptionning PID = %s from server\n", av[1]);
    printf("I must send him the following string: %s\n", av[2]);

    int pid = atoi(av[1]);

    struct sigaction new_action, old_action;

    ret = sigaction(31, )
    // kill(pid, SIGTERM);

    return (0);
}