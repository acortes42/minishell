#include "../minishell.h"

void handle_sigint(int sig) 
{ 
    if (sig == 2)
    {
        ft_putstr("\n    Esto ha terminado con ctrl+c    \n");
        exit(0);
    }
   /* else if (sig == 3)
    {
        ft_putstr("\n    Esto ha terminado con ctlr+/    \n");
        exit(0);
    }*/
    return;
} 
