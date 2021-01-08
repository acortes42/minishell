#include "../minishell.h"

int ft_pwd()
{
   char cwd[PATH_MAX];

   if (getcwd(cwd, sizeof(cwd)) != NULL)
   {
       ft_putstr(cwd);
       ft_putstr("\n");
   }
   else 
       perror("getcwd() error");
   return (1);
}

int     ft_help(abs_struct *base)
{
    int x;

    x = 0;
    ft_putstr("Los comandos disponibles són los siguientes:\n\n");
    while(*base->valid_str && x < 10)
    {
        ft_putstr(*base->valid_str++);
        ft_putstr("\n");
        x++;
    }
    return(1);
}
