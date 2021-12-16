#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

#include <stdio.h>
 
int     main(int ac, char **av)
{
    if (ac != 3)
    {
        printf("Error: usage is as follows:\n './client [PID] [string]'\n");
        return (0);
    }
    printf("Client speaking, I am receptionning PID = %s from server\n", av[1]);
    printf("I must send him the following string: %s\n\n", av[2]);

    int pid = atoi(av[1]);
    printf("pid receptionned: %d\n", pid);

    kill(pid, SIGUSR1);
    return (0);
}