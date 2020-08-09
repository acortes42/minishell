#include "../minishell.h"

void handle_sigint(int sig) 
{ 
    pid_t pid;

    pid = getpid();
    if (sig == 2 && pid == 0)
    {
        ft_printf("hey");
        kill(pid, SIGKILL);
    }
    return;
} 
