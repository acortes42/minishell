#include "../minishell.h"

void handle_sigint(int sig) 
{ 
    pid_t pid;

    pid = getpid();
    if (sig == 2 && pid == 0)
    {
        ft_putstr("hey");
        kill(pid, SIGKILL);
    }
    return;
} 
