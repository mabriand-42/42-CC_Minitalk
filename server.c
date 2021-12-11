#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>

// Il faudrait regarder `nouveau les fonctions autoorrisées

int main()
{
    pid_t   pid_server;
    pid_server = getpid();

    printf("Hi I'm server and this is my PID : %d\n", pid_server);

    pause();
    

    return (0);


}