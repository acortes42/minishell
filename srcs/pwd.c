#include "../minishell.h"

int ft_pwd(abs_struct *base)
{
   char cwd[PATH_MAX];

   if (getcwd(cwd, sizeof(cwd)) != NULL) 
       ft_printf("%s\n", cwd);
   else 
       perror("getcwd() error");
   return (1);
}

int     ft_help(abs_struct *base)
{
    ft_printf("Los comandos disponibles són los siguientes:\n\n");
    while(*base->valid_str)
        ft_printf("%s\n", *base->valid_str++);
    return(1);
}
